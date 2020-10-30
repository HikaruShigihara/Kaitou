using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class y_90 : MonoBehaviour
{
    //public GameObject targetObject;
    static private Vector3 pos;
    bool onoff = false;
    // Start is called before the first frame update
    void Start()
    {
        //pos = targetObject.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(onoff);

        var playerpos = GameObject.Find("Player").transform.position;
        var Cubesrotato = GameObject.Find("Cubes").transform;

        var rotato = Cubesrotato.transform.rotation;
        var rotatoOira = rotato.eulerAngles;

        if (onoff == true)
        {
            if (rotatoOira.y <= 90.0f)
            {
                //回転
                Cubesrotato.RotateAround(playerpos, Vector3.up, 90.0f * Time.deltaTime);
            }
        }
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
