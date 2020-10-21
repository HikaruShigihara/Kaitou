using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Goal_Scenemove : MonoBehaviour
{
    static public int count;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == ("Player"))
        {
            if (count == 0)
            {
                Debug.Log(count);
                SceneManager.LoadScene("2ndstage");
                count = 1;
            }
            else if(count == 1)
            {
                Debug.Log(count);

                SceneManager.LoadScene("3rdstage");
                count = 2;

            }
            else if(count == 2)
            {
                Debug.Log(count);

                SceneManager.LoadScene("GameScene");
                count = 0;

            }
        }
    }
}
