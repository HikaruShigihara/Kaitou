using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CountOperator : MonoBehaviour
{
    public GameObject Count_Object;
    static public int Max_Count = 0;
    static public int Count = Max_Count;

    // Start is called before the first frame update
    void Start()
    {
        if (Goal_Scenemove.count == 0)
        {
            Max_Count = 0;
            Count = Max_Count;
        }

        if (Goal_Scenemove.count == 1)
        {
            Max_Count = 0;
            Count = Max_Count;
        }
        if (Goal_Scenemove.count == 2)
        {
            Max_Count = 0;
            Count = Max_Count;
        }

    }

    // Update is called once per frame
    void Update()
    {
        var Count_Text = Count_Object.GetComponent<Text>();

        if (Count >= 0)
        {
            Count_Text.text = "カウント：" + Count;
        }
    }

}
