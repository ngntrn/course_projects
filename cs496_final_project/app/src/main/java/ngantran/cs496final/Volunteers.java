package ngantran.cs496final;
import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.SimpleAdapter;
import java.util.ArrayList;
import java.util.HashMap;

public class Volunteers extends SimpleAdapter
{

    private Context mContext;
    private ArrayList<HashMap<String,String>> dataList;

    public Volunteers(Context context, ArrayList<HashMap<String,String>> data, int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
        mContext = context;
        dataList = data;
    }

    @Override
    public int getCount() {
        return super.getCount();
    }

    @Override
    public View getView(int idx, View convView, ViewGroup par)
    {
        final int index = idx;
        View v = super.getView(idx, convView, par);
        Button deleteButton;
        deleteButton = v.findViewById(R.id.deleteVolunteerBtn);
        deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, DeleteVolunteerActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("url", dataList.get(index).get("volunteer_self"));
                mContext.startActivity(intent);
            }
        });

        Button editButton;
        editButton = v.findViewById(R.id.editVolunteerBtn);
        editButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mContext, EditVolunteerActivity.class);
                intent.putExtra("name", dataList.get(index).get("name"));
                intent.putExtra("age", dataList.get(index).get("age"));
                intent.putExtra("phone", dataList.get(index).get("phone"));
                intent.putExtra("interests", dataList.get(index).get("interests"));
                intent.putExtra("url", dataList.get(index).get("volunteer_self"));
                mContext.startActivity(intent);
            }
        });

        return v;
    }
}