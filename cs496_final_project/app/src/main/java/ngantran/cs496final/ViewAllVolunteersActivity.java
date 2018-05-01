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

public class ViewAllVolunteersActivity extends AppCompatActivity {

    final String URL = "https://volunteer-projects-app.appspot.com/volunteer";
    OkHttpClient client = new OkHttpClient();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_all_volunteers);
        displayAllVols();
    }

    @Override
    protected void onResume() {
        super.onResume();
        displayAllVols();
    }

    private void displayAllVols() {

        Request req = new Request.Builder()
                .url(URL)
                .build();

        client = new OkHttpClient();
        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                String r = response.body().string();

                try {
                    JSONArray items = new JSONArray(r);
                    final ArrayList<HashMap<String,String>> vols;
                    vols = new ArrayList<HashMap<String,String>>();

                    for (int i = 0; i < items.length(); i++) {
                        HashMap<String,String> p;
                        p = new HashMap<String,String>();
                        p.put("name", "Name: " +
                                items.getJSONObject(i).getString("name"));
                        p.put("age", "Age: " +
                                items.getJSONObject(i).getString("age"));
                        p.put("phone", "Phone Number: " +
                                items.getJSONObject(i).getString("phone"));
                        p.put("interests", "Interests: " +
                                items.getJSONObject(i).getString("interests"));
                        p.put("volunteer_self",
                                items.getJSONObject(i).getString("self"));
                        vols.add(p);
                    }

                    final Volunteers v;
                    v = new Volunteers(
                            ViewAllVolunteersActivity.this,
                            vols,
                            R.layout.all_volunteers_layout,
                            new String[]{"name", "age", "phone", "interests"},
                            new int[]{R.id.allVolunteerName,
                                    R.id.allVolunteerAge,
                                    R.id.allVolunteerPhone,
                                    R.id.allVolunteerInterests}
                    );

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            ListView allVolsListView;
                            allVolsListView = findViewById(R.id.volsListView);
                            allVolsListView.setAdapter(v);
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
