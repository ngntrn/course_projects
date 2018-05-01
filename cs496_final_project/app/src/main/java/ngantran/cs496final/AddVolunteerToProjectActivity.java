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

public class AddVolunteerToProjectActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_volunteer_to_project);
        TextView addVolunteerTextView = findViewById(R.id.AddVolunteerTextView);
        addVolunteerTextView.setText(getIntent().getStringExtra("name") );

        Button addButton = findViewById(R.id.confirmAddVolunteerBtn);
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                addVolunteer(getIntent().getStringExtra("url"),
                        getIntent().getStringExtra("project_id"));
            }
        });
    }

    private void addVolunteer(String url, String project_id)
    {
        String body = "{\"project_id\": " + "\"" + project_id + "\"}";
        Log.d("body:", body);
        Log.d("url:", url);

        MediaType JSON = MediaType.parse("application/json; charset=utf-8");
        OkHttpClient client = new OkHttpClient();
        RequestBody b = RequestBody.create(JSON, body);

        String u = url;
        Request req = new Request.Builder()
                .url(u)
                .put(b)
                .build();

        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull  Call call, final @NonNull Response response) throws IOException
            {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        try{
                            String r = response.body().string();
                            System.out.println("putJSONRequest response.body: "+r);}
                        catch(IOException i)
                        {
                            i.printStackTrace();
                        }


                        if (response.code() == 200)
                        {
                            ((TextView)findViewById(R.id.AddVolunteerTextView)).setText(R.string.volunteerAddedText);
                        }
                        else
                        {
                            ((TextView)findViewById(R.id.AddVolunteerTextView)).setText(R.string.volunteerAddError);
                        }
                    }
                });
            }
        });
    }
}