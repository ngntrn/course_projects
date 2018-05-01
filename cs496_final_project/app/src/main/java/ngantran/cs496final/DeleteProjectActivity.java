package ngantran.cs496final;
import android.support.v7.app.AppCompatActivity;
import android.support.annotation.NonNull;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.io.IOException;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class DeleteProjectActivity extends AppCompatActivity {

    final String BASE_URL = "https://volunteer-projects-app.appspot.com/";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_delete_project);
        TextView deleteProjectTextView;
        deleteProjectTextView = (TextView) findViewById(R.id.deleteProjectTextView);
        deleteProjectTextView.setText( getIntent().getStringExtra("name"));

        Button deleteButton = (Button) findViewById(R.id.confirmDeleteProjectBtn);
        deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                deleteProject(getIntent().getStringExtra("url"));
            }
        });
    }

    private void deleteProject(String dUrl) {

        Request req = new Request.Builder()
                .url(dUrl)
                .delete()
                .build();

        OkHttpClient client;
        client = new OkHttpClient();
        client.newCall(req).enqueue(new Callback()
        {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e)
            {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull final Response response) throws IOException
            {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (response.code() == 204) {
                            ((TextView)findViewById(R.id.deleteProjectTextView)).setText(R.string.projectedRemovedText);
                        } else {
                            ((TextView)findViewById(R.id.deleteProjectTextView)).setText(R.string.projectRemoveErrorText);
                        }
                    }
                });
            }
        });
    }
}