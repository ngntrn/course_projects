package ngantran.cs496final;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // show all Projects
        Button allProjectsButton = (Button) findViewById(R.id.viewAllProjectsBtn);
        allProjectsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, ViewAllProjectsActivity.class);
                startActivity(i);
            }
        });

        // show all Volunteers
        Button allVolsButton = (Button) findViewById(R.id.viewAllVolunteersBtn);
        allVolsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, ViewAllVolunteersActivity.class);
                startActivity(i);
            }
        });

        // add a new Project
        Button newPersonButton = (Button) findViewById(R.id.addProjectBtn);
        newPersonButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, AddProjectActivity.class);
                startActivity(i);
            }
        });

        // add a new Volunteer
        Button newVolButton = findViewById(R.id.addVolunteerBtn);
        newVolButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, AddVolunteerActivity.class);
                startActivity(i);
            }
        });
    }
}