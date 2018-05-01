package ngantran.cs496final;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class AddProjectActivity extends AppCompatActivity {

    final String URL = "https://volunteer-projects-app.appspot.com/project";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_project);

        Button newProjectButton = findViewById(R.id.newProjectBtn);
        newProjectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                String name = ((TextView)findViewById(R.id.newProjectNameText)).getText().toString();
                String date = ((TextView)findViewById(R.id.newProjectDateText)).getText().toString();
                String category = ((TextView)findViewById(R.id.newProjectCategoryText)).getText().toString();
                String location = ((TextView)findViewById(R.id.newProjectLocationText)).getText().toString();

                Log.d("project Name: ", name);
                Log.d("date: " , date);
                Log.d("category: ", String.valueOf(category));
                Log.d("location: ", location);

                // create json string to send in post request
                String body = "{\"name\": \"" + name + "\", \"date\": \"" + date + "\", " +
                        "\"category\": \"" + category + "\", \"location\": \"" + location + "\"}";
                Log.d("body string: ", body);

                MediaType JSON = MediaType.parse("application/json; charset=utf-8");
                OkHttpClient client = new OkHttpClient();
                okhttp3.RequestBody b = RequestBody.create(JSON, body);

                okhttp3.Request request = new Request.Builder()
                        .url(URL)
                        .post(b)
                        .build();

                client = new OkHttpClient();
                client.newCall(request).enqueue(new Callback()
                {
                    @Override
                    public void onFailure(@NonNull Call call, @NonNull IOException e)
                    {
                        e.printStackTrace();
                    }

                    @Override
                    public void onResponse(@NonNull  Call call, @NonNull Response response) throws IOException
                    {
                        String r = response.body().string();
                        System.out.println("postJSONRequest response.body: "+r);

                        try {
                            JSONObject item = new JSONObject(r);
                            final String newname = item.getString("name");
                            final String newdate = item.getString("date");
                            final String newcategory = item.getString("category");
                            final String newlocation = item.getString("location");

                            runOnUiThread(new Runnable()
                            {
                                @Override
                                public void run() {
                                    ((TextView)findViewById(R.id.newProjectName)).setText(newname);
                                    ((TextView)findViewById(R.id.newProjectDate)).setText(newdate);
                                    ((TextView)findViewById(R.id.newProjectCategory)).setText(newcategory);
                                    ((TextView)findViewById(R.id.newProjectLocation)).setText(newlocation);
                                }
                            });
                        } catch (JSONException je)
                        {
                            je.printStackTrace();
                        }
                    }
                });
            }
        });
    }
}
