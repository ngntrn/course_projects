package ngantran.cs496final;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.util.Log;
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

public class ViewProjectVolunteersActivity extends AppCompatActivity
{

    String url = "https://volunteer-projects-app.appspot.com/";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_project_volunteers);
        String id = getIntent().getStringExtra("url");
        Log.d("project url:", id);
        String proj_id = id.substring(51);
        Log.d("project id:", proj_id);
        displayProjectVolunteers(proj_id);

    }

    @Override
    protected void onResume()
    {
        super.onResume();
        String id = getIntent().getStringExtra("url");
        Log.d("project url:", id);
        String proj_id = id.substring(51);
        Log.d("project id:", proj_id);
        displayProjectVolunteers(proj_id);
    }

    private void displayProjectVolunteers(String proj_id)
    {

        String u = url + proj_id;
        Log.d("url", u);
        Request req = new Request.Builder()
                .url(u)
                .build();

        OkHttpClient client = new OkHttpClient();
        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException
            {

                String r = response.body().string();

                try {
                    JSONArray items = new JSONArray(r);
                    ArrayList<HashMap<String,String>> plants;
                    plants = new ArrayList<HashMap<String,String>>();

                    for (int i = 0; i < items.length(); i++)
                    {
                        HashMap<String,String> v;
                        v = new HashMap<String,String>();
                        v.put("name", "Name: " +
                                items.getJSONObject(i).getString("name"));
                        v.put("age", "Age: " +
                                items.getJSONObject(i).getString("age"));
                        v.put("phone", "Phone Number: " +
                                items.getJSONObject(i).getString("phone"));
                        v.put("interests", "Interests: " +
                                items.getJSONObject(i).getString("interests"));
                        v.put("volunteer_self",
                                items.getJSONObject(i).getString("self"));
                        plants.add(v);
                    }

                    final ProjectVolunteers adapter;
                    adapter = new ProjectVolunteers(
                            ViewProjectVolunteersActivity.this,
                            plants,
                            R.layout.project_volunteers_layout,
                            new String[]{"name","age","phone","interests"},
                            new int[]{R.id.projectVolName,
                                    R.id.projectVolAge,
                                    R.id.projectVolPhone,
                                    R.id.projectVolInterests}
                    );

                    runOnUiThread(new Runnable()
                    {
                        @Override
                        public void run()
                        {
                            ListView allVolunteersViewList;
                            allVolunteersViewList = (ListView)
                                    findViewById(R.id.projectVolunteersListView);
                            allVolunteersViewList.setAdapter(adapter);
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