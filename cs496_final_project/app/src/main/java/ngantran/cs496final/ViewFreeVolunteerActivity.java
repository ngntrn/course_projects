package ngantran.cs496final;

import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
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

public class ViewFreeVolunteerActivity extends AppCompatActivity {

    final String URL = "https://volunteer-projects-app.appspot.com/no_project";
    String project_id;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_free_volunteers);
        project_id = getIntent().getStringExtra("project_id");
        displayVolunteers(project_id);
    }

    @Override
    protected void onResume() {
        super.onResume();
        displayVolunteers(project_id);
    }

    private void displayVolunteers(final String project_id) {
        Request req = new Request.Builder()
                .url(URL)
                .build();

        OkHttpClient client;
        client = new OkHttpClient();
        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {

                final String r = response.body().string();

                try {
                    JSONArray items = new JSONArray(r);
                    ArrayList<HashMap<String,String>> vols;
                    vols = new ArrayList<HashMap<String,String>>();

                    for (int i = 0; i < items.length(); i++) {
                        HashMap<String,String> v;
                        v = new HashMap<String,String>();
                        v.put("project_id", project_id);
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
                        vols.add(v);
                    }

                    final AddVolunteerToProject adapter;
                    adapter = new AddVolunteerToProject(
                            ViewFreeVolunteerActivity.this,
                            vols,
                            R.layout.volunteers_no_project_layout,
                            new String[]{"name","age","phone","interests"},
                            new int[]{R.id.fVolName,
                                    R.id.fVolAge,
                                    R.id.fVolPhone,
                                    R.id.fVolInterests}
                    );

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            ListView allVolunteersListView;
                            allVolunteersListView = (ListView)
                                    findViewById(R.id.fVolunteersListView);
                            allVolunteersListView.setAdapter(adapter);
                        }
                    });
                } catch (JSONException je) {
                    je.printStackTrace();
                }
            }
        });
    }
}