﻿using System;
using System.Threading.Tasks;

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class kaiten : MonoBehaviour
{
    float angle = 90.0f;
    private Vector3 targetPos;
    int ABXY = 0;
    //int rotatoFlag;
    bool rotatoFlag0 = false;
    bool rotatoFlag1 = false;
    bool rotatoFlag2 = false;
    bool rotatoFlag3 = false;
    bool rotatoFlag4 = true;

    bool zeromin_X = false;
    bool zeromax_X = false;
    bool zeromin_Z = false;
    bool zeromax_Z = false;

    private bool A = false;
    private bool B = false;
    private bool Y = false;
    private bool X = false;

    
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        var rotato = GameObject.Find("Cubes").transform.rotation;

        RotatoStage();
        Debug.Log(rotato.z);


        if (Y == true)
        {
            transform.RotateAround(targetPos, transform.right, angle * Time.deltaTime);
        }
        if (A == true)
        {
            transform.RotateAround(targetPos, transform.right, -angle * Time.deltaTime);
        }
        if (B == true)
        {
            transform.RotateAround(targetPos, transform.forward, -angle * Time.deltaTime);
        }
        if (X == true)
        {
            transform.RotateAround(targetPos, transform.forward, angle * Time.deltaTime);
        }
    }

    void KeyOperation()
    {
        if (Key.Y == 1)
        {
            //ABXY = 4;
            Y = true;
            CountOperator.Count += 1;

        }
        if (Key.A == 1)
        {
            //ABXY = 1;
            A = true;
            CountOperator.Count += 1;

        }
        if (Key.X == 1)
        {
            //ABXY = 3;
            X = true;
            CountOperator.Count += 1;

        }
        if (Key.B == 1)
        {
            //ABXY = 2;
            B = true;
            CountOperator.Count += 1;

        }

    }

    void RotatoStage()
    {
        var rotato = GameObject.Find("Cubes").transform.rotation;
        var target = GameObject.Find("Player").transform;
        targetPos = target.position;
        KeyOperation();
        //0度のときX軸
        if (0.0f >= rotato.x && zeromax_X == true)
        {
            Y = false;
            A = false;
            zeromax_X = false;
            KeyOperation();
        }
        if (0.0f <= rotato.x && zeromin_X == true)
        {
            Y = false;
            A = false;
            zeromin_X = false;
            KeyOperation();
        }

        //0度のときZ軸
        if (0.0f >= rotato.z && zeromax_Z == true && rotatoFlag3 == true)
        {
            rotatoFlag3 = false;
            rotatoFlag0 = true;
            rotatoFlag2 = true;
            X = false;
            B = false;
            zeromax_Z = false;
            KeyOperation();
        }
        else if (0.0f <= rotato.z && zeromin_Z == true && rotatoFlag3 == true)
        {
            rotatoFlag3 = false;
            rotatoFlag0 = true;
            rotatoFlag2 = true;
            X = false;
            B = false;
            zeromin_Z = false;
            KeyOperation();
        }


        if (0.7f <= rotato.x)
        {
            Y = false;
            A = false;
            zeromax_X = true;
            KeyOperation();
        }

        if (-0.7f >= rotato.x)
        {
            Y = false;
            A = false;
            zeromin_X = true;
            KeyOperation();
        }
        //始めの一回だけ処理
        if (0.7f <= rotato.z && rotatoFlag4 == true)
        {
            rotatoFlag1 = true;
            rotatoFlag3 = true;
            rotatoFlag4 = false;
            rotatoFlag0 = false;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }
        if (-0.7f >= rotato.z && rotatoFlag4 == true)
        {
            rotatoFlag1 = true;
            rotatoFlag3 = true;
            rotatoFlag4 = false;
            rotatoFlag2 = false;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }

        //ここからループ
        if (0.7f <= rotato.z && rotatoFlag0 == true)
        {
            rotatoFlag1 = true;
            rotatoFlag0 = false;
            rotatoFlag3 = true;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }
        else if (-0.7f >= rotato.z && rotatoFlag2 == true)
        {
            rotatoFlag1 = true;
            rotatoFlag3 = true;
            rotatoFlag2 = false;

            X = false;
            B = false;
            zeromin_Z = true;
            KeyOperation();

        }
        else if (0.99999f <= rotato.z && rotatoFlag1 == true)
        {
            rotatoFlag2 = true;
            rotatoFlag1 = false;
            rotatoFlag0 = true;
            X = false;
            B = false;

            zeromax_Z = true;
            KeyOperation();
        }
        else if (-0.9999f >= rotato.z && rotatoFlag1 == true)
        {
            rotatoFlag2 = true;
            rotatoFlag1 = false;
            rotatoFlag0 = true;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }
        else if (0.7f >= rotato.z && rotatoFlag2 == true)
        {
            rotatoFlag3 = true;
            rotatoFlag2 = false;
            rotatoFlag1 = true;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }
        else if (-0.7f <= rotato.z && rotatoFlag0 == true)
        {
            rotatoFlag1 = true;
            rotatoFlag0 = false;
            rotatoFlag3 = true;
            X = false;
            B = false;
            zeromax_Z = true;
            KeyOperation();
        }

    }

}
