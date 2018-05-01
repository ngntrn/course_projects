package ngantran.cs496final;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import org.json.JSONObject;
import org.json.JSONException;
import java.io.IOException;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class AddVolunteerActivity extends AppCompatActivity {

    final String BASE_URL = "https://volunteer-projects-app.appspot.com/volunteer";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_volunteer);
        Button newPlantBtn = findViewById(R.id.newVolunteerBtn);
        newPlantBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {

                String name = ((TextView)findViewById(R.id.newVolunteerNameText)).getText().toString();
                int age = Integer.parseInt(((TextView)findViewById(R.id.newVolunteerAgeText)).getText().toString());
                String phone = ((TextView)findViewById(R.id.newVolunteerPhoneText)).getText().toString();
                String interests = ((TextView)findViewById(R.id.newVolunteerInterestsText)).getText().toString();

                Log.d("name: ", name);
                Log.d("age: " , String.valueOf(age));
                Log.d("phone: " , phone);
                Log.d("interests: " , interests);

                // create json string to send in post request
                String body = "{\"name\": \"" + name + "\", \"age\": " + age + ", " +
                        "\"phone\": \"" + phone + "\", \"interests\": \"" + interests + "\"}";
                Log.d("body string: ", body);

                MediaType JSON = MediaType.parse("application/json; charset=utf-8");
                OkHttpClient client;
                Request request;
                RequestBody b = RequestBody.create(JSON, body);

                request = new Request.Builder()
                        .url(BASE_URL)
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
                    public void onResponse(@NonNull Call call,@NonNull Response response) throws IOException
                    {
                        String r = response.body().string();
                        System.out.println("postJSONRequest response.body: "+r);

                        try {
                            JSONObject item = new JSONObject(r);
                            final String newname = item.getString("name");
                            final String newage = item.getString("age");
                            final String newphone = item.getString("phone");
                            final String newinterests = item.getString("interests");


                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    ((TextView)findViewById(R.id.newVolunteerName)).setText(newname);
                                    ((TextView)findViewById(R.id.newVolunteerAge)).setText(newage);
                                    ((TextView)findViewById(R.id.newVolunteerPhone)).setText(newphone);
                                    ((TextView)findViewById(R.id.newVolunteerInterests)).setText(newinterests);
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