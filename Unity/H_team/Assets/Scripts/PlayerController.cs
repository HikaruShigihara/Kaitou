using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;
public class PlayerController : MonoBehaviour
{
    Vector3 m_move = new Vector3(0.0f, 0.0f, 0.0f);

    //float m_defaultSpeed = 0.08f;
    float m_walkSpeed = 1.5f;

    Vector3 m_trans = new Vector3(0.0f, 0.0f, 0.0f);
    Vector3 m_limits = new Vector3(0.0f, -30.0f, 0.0f);
    Vector3 m_respawn = new Vector3(0.0f, 3.0f, 0.0f);

    float m_speed;
    public GameObject Cubes;
    bool m_moveFrag = false;

    void Start()
    {
        //r_rigid = GetComponent<Rigidbody>();
    }

    //void FixedUpdate()
    //{
    //    r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    //}

    void Update()
    {
        Move();
        transform.Translate(m_move);
        Respawn();
    }


    void Move()
    {
        //if (Key.right == 1)
        //{
        //    m_move.x = m_walkSpeed;
        //    CountOperator.Count -= 1;
        //}
        //else if (Key.left == 1)
        //{
        //    m_move.x = -m_walkSpeed;
        //    CountOperator.Count -= 1;
        //}
        //else
        //{
        //    m_move.x = 0.0f;
        //}
        //if (Key.up == 1)
        //{
        //    m_move.z = m_walkSpeed;
        //    CountOperator.Count -= 1;
        //}
        //else if (Key.down == 1)
        //{
        //    m_move.z = -m_walkSpeed;
        //    CountOperator.Count -= 1;
        //}
        //else
        //{
        //    m_move.z = 0.0f;
        //}
        if(Key.padX == 0 && Key.padY == 0)
        {
            m_moveFrag = true;
        }

        if (m_moveFrag == true && Key.padX > 0)
        {
            m_move.x = m_walkSpeed;
            CountOperator.Count += 1;
            m_moveFrag = false;
        }
        else if (m_moveFrag == true && Key.padX < 0)
        {
            m_move.x = -m_walkSpeed;
            CountOperator.Count += 1;
            m_moveFrag = false;
        }
        else
        {
            m_move.x = 0.0f;
        }

        if (m_moveFrag == true && Key.padY > 0)
        {
            m_move.z = m_walkSpeed;
            CountOperator.Count += 1;
            m_moveFrag = false;
        }
        else if (m_moveFrag == true && Key.padY < 0)
        {
            m_move.z = -m_walkSpeed;
            CountOperator.Count += 1;
            m_moveFrag = false;
        }
        else
        {
            m_move.z = 0.0f;
        }

    }

    void Respawn()
    {
        m_trans = transform.position;

        if(m_trans.y < m_limits.y)
        {
            //m_move = Vector3.zero;
            //transform.position = m_respawn;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            CountOperator.Count = CountOperator.Max_Count;
        }
        if(Input.GetKeyDown(KeyCode.DownArrow))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            CountOperator.Count = CountOperator.Max_Count;
        }
    }
    //private void OnCollisionEnter(Collision collision)
    //{
    //    if(collision.gameObject.tag != ("Goal"))
    //    {
    //        if (CountOperator.Count == 0)
    //        {
    //            //m_move = Vector3.zero;
    //            //transform.position = m_respawn;
    //            SceneManager.LoadScene(SceneManager.GetActiveScene().name);

    //            CountOperator.Count = CountOperator.Max_Count;
    //        }

    //    }
    //}

    //if (Key.up == 1)
    //{
    //    transform.Translate(0f, 0f, 1.5f);
    //}
    //if (Input.GetKeyDown(KeyCode.E))
    //{
    //    transform.Translate(0f, 0f, -1.5f);
    //}
    //if (Input.GetKeyDown(KeyCode.A))
    //{
    //    transform.Translate(-1.5f, 0f, 0f);
    //}
    //if (Input.GetKeyDown(KeyCode.D))
    //{
    //    transform.Translate(1.5f, 0f, 0f);
    //}
    //if (Key.A == 1 && m_jump)
    //{
    //    r_rigid.velocity = new Vector3(r_rigid.velocity.x, m_jumpPower, r_rigid.velocity.z);
    //    m_jump = false;
    //}


}
