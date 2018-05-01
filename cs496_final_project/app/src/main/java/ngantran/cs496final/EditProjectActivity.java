package ngantran.cs496final;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import java.io.IOException;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class EditProjectActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_project);

        final TextView oldName = findViewById(R.id.editProjectName);
        final TextView oldDate = findViewById(R.id.editProjectDate);
        final TextView oldCategory = findViewById(R.id.editProjectCategory);
        final TextView oldLocation = findViewById(R.id.editProjectLocation);

        final String oldNameText = getIntent().getStringExtra("name");
        final String oldDateText = getIntent().getStringExtra("date");
        final String oldCategoryText = getIntent().getStringExtra("category");
        final String oldLocationText = getIntent().getStringExtra("location");

        oldName.setText(oldNameText);
        oldDate.setText(oldDateText);
        oldCategory.setText(oldCategoryText);
        oldLocation.setText(oldLocationText);

        final EditText newNameEdit = findViewById(R.id.newNameText);
        final EditText newDateEdit = findViewById(R.id.newDateText);
        final EditText newCategoryEdit = findViewById(R.id.newCategoryText);
        final EditText newLocationEdit = findViewById(R.id.newLocationText);

        newNameEdit.setHint(oldNameText);
        newDateEdit.setHint(oldDateText);
        newCategoryEdit.setHint(oldCategoryText);
        newLocationEdit.setHint(oldLocationText);

        Button editProjectBtn = (Button)findViewById(R.id.submitProjectEditBtn);
        editProjectBtn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {

                String newName = newNameEdit.getText().toString();
                if (newName.equals(""))
                {
                    newName = oldNameText.substring(14) ;
                    Log.d("old name:" , oldNameText);
                }

                String newDate = newDateEdit.getText().toString();
                if (newDate.equals(""))
                {
                    newDate = oldDateText.substring(6);
                }

                String newCategory = newCategoryEdit.getText().toString();
                if (newCategory.equals(""))
                {
                    newCategory = oldCategoryText.substring(10);
                }

                String newLocation = newLocationEdit.getText().toString();
                if (newLocation.equals(""))
                {
                    newLocation = oldLocationText.substring(10);
                }

                String newUrl = getIntent().getStringExtra("url");
                editProject(newUrl, newName, newDate, newCategory, newLocation);
            }
        });
    }

    private void editProject(String url, String name, String date, String category, String location)
    {

        Log.d("url:", url);

        String body = "{\"name\": \"" + name + "\", \"date\": \"" + date +
                "\", \"category\": \"" + category + "\", \"location\": \"" + location + "\"}";

        Log.d("body:", body);

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
            public void onFailure(@NonNull Call call,@NonNull IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, final @NonNull Response response) throws IOException
            {

                String r = response.body().string();
                System.out.println("postJSONRequest response.body: "+r);

            }
        });
    }
}