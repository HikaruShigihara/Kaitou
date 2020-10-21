using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class _Switch_clision : MonoBehaviour
{

    // 自身の保持ナンバー
    [SerializeField]
    private uint myNumber ;


    // 親に通知のため
    private State_SwitchManage _SwitchManager;

    // Start is called before the first frame update
    void Start()
    {
        _SwitchManager = transform.parent.gameObject.GetComponent<State_SwitchManage>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag == "Player")
        {
            // 接触してきたのがプレイヤーだった場合、親に自分自身のマイナンバーを通知する
            _SwitchManager.sendMyNumber(myNumber);
        }
    }

}
