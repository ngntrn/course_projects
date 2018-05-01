package ngantran.cs496final;

import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;

public class Projects extends SimpleAdapter
{

    private Context mContext;
    private ArrayList<HashMap<String,String>> dataList;

    public Projects(Context context, ArrayList<HashMap<String,String>> data, int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
        mContext = context;
        dataList = data;
    }

    @Override
    public int getCount()
    {
        return super.getCount();
    }

    @Override
    public View getView(int idx, View convView, ViewGroup par)
    {
        final int index = idx;
        View v = super.getView(idx, convView, par);

        // delete Project Button
        Button deleteButton;
        deleteButton = (Button) v.findViewById(R.id.deleteProjectBtn);
        deleteButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, DeleteProjectActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("url", dataList.get(index).get("project_self"));
                mContext.startActivity(intent);
            }
        });

        // edit Project button
        Button editButton;
        editButton = (Button) v.findViewById(R.id.editProjectBtn);
        editButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, EditProjectActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("date", dataList.get(index).get("date"));
                intent.putExtra("category", dataList.get(index).get("category"));
                intent.putExtra("location", dataList.get(index).get("location"));
                intent.putExtra("url", dataList.get(index).get("project_self"));
                mContext.startActivity(intent);
            }
        });

        // view Volunteers Button
        Button viewVolsButton;
        viewVolsButton = (Button) v.findViewById(R.id.projectViewVolsBtn);
        viewVolsButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, ViewProjectVolunteersActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("url", dataList.get(index).get("project_self"));
                mContext.startActivity(intent);
            }
        });

        // add Volunteers button
        Button addVolButton;
        addVolButton = (Button) v.findViewById(R.id.projectAddVolsBtn);
        addVolButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(mContext, ViewFreeVolunteerActivity.class);
                intent.putExtra("project_id", dataList.get(index).get("project_id"));
                mContext.startActivity(intent);
            }
        });

        return v;
    }
}