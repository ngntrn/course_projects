package ngantran.cs496final;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class ViewAllProjectsActivity extends AppCompatActivity
{

    final String URL = "https://volunteer-projects-app.appspot.com/";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_all_projects);
        displayAllProjects();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        displayAllProjects();
    }

    private void displayAllProjects()
    {
        Request req = new Request.Builder()
                .url(URL + "project")
                .build();

        OkHttpClient client;
        client = new OkHttpClient();
        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(Call call, IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException
            {
                String r = response.body().string();
                try
                {
                    JSONArray items = new JSONArray(r);
                    ArrayList<HashMap<String,String>> projects;
                    projects = new ArrayList<HashMap<String,String>>();

                    for (int i = 0; i < items.length(); i++)
                    {
                        HashMap<String,String> p;
                        p = new HashMap<String,String>();
                        p.put("project_id",
                                items.getJSONObject(i).getString("id"));
                        p.put("name", "Project Name: " +
                                items.getJSONObject(i).getString("name"));
                        p.put("date", "Date: " +
                                items.getJSONObject(i).getString("date"));
                        p.put("category", "Category: " +
                                items.getJSONObject(i).getString("category"));
                        p.put("location", "Location: " +
                                items.getJSONObject(i).getString("location"));
                        p.put("project_self",
                                items.getJSONObject(i).getString("self"));
                        projects.add(p);
                    }

                    final Projects g;
                    g = new Projects(
                            ViewAllProjectsActivity.this,
                            projects,
                            R.layout.all_projects_layout,
                            new String[]{"name","date","category","location"},
                            new int[]{R.id.allProjectName,
                                    R.id.allProjectDate,
                                    R.id.allProjectCategory,
                                    R.id.allProjectLocation}
                    );

                    runOnUiThread(new Runnable()
                    {
                        @Override
                        public void run() {
                            ListView allProjectsListView;
                            allProjectsListView = (ListView)
                                    findViewById(R.id.projectsListView);
                            allProjectsListView.setAdapter(g);
                        }
                    });
                } catch (JSONException je)
                {
                    je.printStackTrace();
                }
            }
        });
    }
}