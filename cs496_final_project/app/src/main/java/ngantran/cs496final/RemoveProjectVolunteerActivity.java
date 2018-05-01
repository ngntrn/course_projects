package ngantran.cs496final;


import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class RemoveProjectVolunteerActivity extends AppCompatActivity {

    String url = "https://volunteer-projects-app.appspot.com/";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_remove_project_volunteer);
        TextView removeVolunteerTextView = (TextView) findViewById(R.id.removeVolunteerTextView);
        removeVolunteerTextView.setText(getIntent().getStringExtra("name") );

        String id = getIntent().getStringExtra("url");
        Log.d("volunteer url", id);
        final String vol_id = id.substring(53);
        Log.d("volunteer id:", vol_id);

        Button removeButton = (Button) findViewById(R.id.confirmRemoveVolunteerBtn);
        removeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                removeVolunteer(vol_id);
            }
        });
    }

    private void removeVolunteer(String vol_id) {
        String body = "";


        MediaType JSON = MediaType.parse("application/json; charset=utf-8");
        OkHttpClient client = new OkHttpClient();
        okhttp3.RequestBody b = RequestBody.create(JSON, body);
        String patch_url =  url + vol_id;
        Log.d("patch url",patch_url);

        Request req = new Request.Builder()
                .url(patch_url)
                .patch(b)
                .build();

        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull  Call call, @NonNull  IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, final @NonNull  Response response) throws IOException
            {
                try{
                    String r = response.body().string();
                    System.out.println("patchJSONRequest response.body: "+r);}
                catch(IOException i)
                {
                    i.printStackTrace();
                }

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (response.code() == 200)
                        {
                            ((TextView)findViewById(R.id.removeVolunteerTextView)).setText(R.string.volunteerRemovedText);
                        } else {
                            ((TextView)findViewById(R.id.removeVolunteerTextView)).setText(R.string.volunteerRemoveErrorText);
                        }
                    }
                });
            }
        });
    }
}
