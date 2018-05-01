package ngantran.cs496final;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
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

public class EditVolunteerActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_volunteer);

        // set the volunteer attributes
        final TextView oldName = findViewById(R.id.editVolName);
        final TextView oldAge = findViewById(R.id.editVolAge);
        final TextView oldPhone = findViewById(R.id.editVolPhone);
        final TextView oldInterests = findViewById(R.id.editVolInterests);

        final String oldNameText = getIntent().getStringExtra("name");
        final String oldAgeText = getIntent().getStringExtra("age");
        final String oldPhoneText = getIntent().getStringExtra("phone");
        final String oldInterestsText = getIntent().getStringExtra("interests");

        oldName.setText(oldNameText);
        oldAge.setText(oldAgeText);
        oldPhone.setText(oldPhoneText);
        oldInterests.setText(oldInterestsText);

        // set tbe hints
        final EditText newNameEdit = findViewById(R.id.newNameEditText);
        final EditText newAgeEdit = findViewById(R.id.newAgeEditText);
        final EditText newPhoneEdit = findViewById(R.id.newPhoneEditText);
        final EditText newInterestsEdit = findViewById(R.id.newInterestsEditText);

        newNameEdit.setHint(oldNameText);
        newAgeEdit.setHint(oldAgeText);
        newPhoneEdit.setHint(oldPhoneText);
        newInterestsEdit.setHint(oldInterestsText);


        Button editVolunteerButton = findViewById(R.id.submitVolunteerEditBtn);
        editVolunteerButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {
                // the new values
                String newAge = newAgeEdit.getText().toString();
                if (newAge.equals(""))
                {
                    newAge = oldAgeText.substring(5);
                }
                int newAgeInt = Integer.parseInt(newAge);

                String newName = newNameEdit.getText().toString();
                if (newName.equals("")) {
                    newName = oldNameText.substring(6);
                }

                String newPhone = newPhoneEdit.getText().toString();
                if (newPhone.equals("")) {
                    newPhone = oldPhoneText.substring(14);
                }

                String newInterests = newInterestsEdit.getText().toString();
                if (newInterests.equals("")) {
                    newInterests = oldInterestsText.substring(11);
                }

                String newUrl = getIntent().getStringExtra("url");

                editVolunteer(newUrl, newName, newAgeInt, newPhone, newInterests);
            }
        });
    }

    private void editVolunteer(String url, String name, int age, String phone, String interests)
    {
        String body = "{\"name\": \"" + name + "\", \"age\": " +
                age + ", \"phone\": \"" + phone + "\", \"interests\": \"" + interests + "\"}";

        MediaType JSON = MediaType.parse("application/json; charset=utf-8");
        OkHttpClient client = new OkHttpClient();
        okhttp3.RequestBody b = RequestBody.create(JSON, body);

        Request req = new Request.Builder()
                .url(url)
                .patch(b)
                .build();

        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, final @NonNull Response response) throws IOException
            {

                String r = response.body().string();
                System.out.println("postJSONRequest response.body: "+r);

                try
                {
                    JSONObject item = new JSONObject(r);
                    final String newname = item.getString("name");
                    final String newage = item.getString("age");
                    final String newphone = item.getString("phone");
                    final String newinterests = item.getString("interests");

                    runOnUiThread(new Runnable()
                    {
                        @Override
                        public void run() {
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