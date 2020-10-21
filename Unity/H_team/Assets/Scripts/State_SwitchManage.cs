using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_SwitchManage : MonoBehaviour
{
    protected uint _switchCount = 0;

    protected int _flowSwitchNo = 0;
    public int FlowSwitchNo
    {
        get { return _flowSwitchNo; }
    }
    public uint SwitchCount;
    public GameObject Goal;
    bool onoff = false;
    private Vector3 pos;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        pos = Goal.transform.position;
        if(onoff == true && pos.y <= 0)
        {
            pos.y += 0.3f;
            Goal.transform.position = pos;
        }
    }

    public void sendMyNumber(uint myNumber)
    {
        // 次に踏むナンバーとマイナンバーが同じであれば
        if (myNumber == _flowSwitchNo)
        {
            // 次に踏むナンバーをインクリメントする
            _flowSwitchNo++;
        }
        else
        {
            // 間違っていた場合はリセットする
            _flowSwitchNo = 0;
        }

        // 正解チェック
        _checkSuccess();
    }

    // 正解チェック
    private void _checkSuccess()
    {
        if (_flowSwitchNo == SwitchCount)
        {
            //Goal.transform.position = new Vector3(6.0f, 0.0f, 0.0f);
            onoff = true;
        }
    }

}
