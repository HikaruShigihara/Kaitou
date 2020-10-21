using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Blockswitch : MonoBehaviour
{
    public GameObject targetObject;
    static private Vector3 pos;
    bool onoff = false;
    // Start is called before the first frame update
    void Start()
    {
       pos = targetObject.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
            Debug.Log(onoff);

        if(onoff == true && pos.y <= 1.5f)
        {
            pos.y += 0.1f;
            targetObject.transform.position = pos;
        }
        //if(targetObject.transform.position.y == 1.5f)
        //{

        //}
    }

    private void OnCollisionEnter(Collision collision)
    {
        //Sphereが衝突したオブジェクトがPlaneだった場合
        if (collision.gameObject.tag == "Player")
        {
            onoff = true;
        }

    }
}
