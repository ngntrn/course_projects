package ngantran.cs496final;

import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;

public class ProjectVolunteers extends SimpleAdapter {
    private Context mContext;
    private ArrayList<HashMap<String,String>> dataList;


    public ProjectVolunteers(Context context, ArrayList<HashMap<String,String>> data, int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
        mContext = context;
        dataList = data;
    }


    @Override
    public View getView(int idx, View convView, ViewGroup par) {
        final int index = idx;
        View v = super.getView(idx, convView, par);
        Button removeVolButton;
        removeVolButton = v.findViewById(R.id.removeProjectVolunteerBtn);
        removeVolButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, RemoveProjectVolunteerActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("url", dataList.get(index).get("volunteer_self"));
                intent.putExtra("project_id", dataList.get(index).get("project_id"));
                mContext.startActivity(intent);
            }
        });

        return v;
    }
}