using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class x_180 : MonoBehaviour
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
        var playerpos = GameObject.Find("Player").transform.position;
        var Cubesrotato = GameObject.Find("Cubes").transform;

        var rotato = Cubesrotato.transform.rotation;
        var rotatoOira = rotato.eulerAngles;

        if (onoff == true)
        {
            if (rotatoOira.y <= 90.0f)
            {
                //回転
                Cubesrotato.RotateAround(playerpos, Vector3.forward, 90.0f * Time.deltaTime);
            }
        }
        Debug.Log(rotatoOira);

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
