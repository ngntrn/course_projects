package ngantran.cs496final;
import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.SimpleAdapter;
import java.util.ArrayList;
import java.util.HashMap;

public class AddVolunteerToProject extends SimpleAdapter
{

    private Context mContext;
    private ArrayList<HashMap<String,String>> dataList;

    public AddVolunteerToProject(Context context, ArrayList<HashMap<String,String>> data, int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
        mContext = context;
        dataList = data;
    }

    @Override
    public int getCount() {
        return super.getCount();
    }

    @Override
    public View getView(int pos, View convView, ViewGroup par) {
        final int position = pos;
        View v = super.getView(pos, convView, par);
        Button addVolunteerBtn = (Button) v.findViewById(R.id.addProjectVolunteerBtn);
        addVolunteerBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, AddVolunteerToProjectActivity.class);
                intent.putExtra("name", dataList.get(position).get("name"));
                intent.putExtra("url", dataList.get(position).get("volunteer_self"));
                intent.putExtra("project_id", dataList.get(position).get("project_id"));
                mContext.startActivity(intent);
            }
        });
        return v;
    }
}