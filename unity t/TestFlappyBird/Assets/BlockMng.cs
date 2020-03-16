using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockMng : MonoBehaviour
{
    // Start is called before the first frame update
    // 生成するﾌﾞﾛｯｸ
    public GameObject block;

    // 0になったらﾌﾞﾛｯｸを生成する
    float _timer;

    // トータル時間保持用
    float _totalTime;

    // ﾌﾞﾛｯｸの生成回数ｶｳﾝﾄ用
    int _cnt;

    void Start()
    {
        _timer = 0;
        _totalTime = 0;
        _cnt = 0;
    }

    // Update is called once per frame
    void Update()
    {
        _timer -= Time.deltaTime;

        _totalTime += Time.deltaTime;

        if(_timer <= 0)
        {
            // 0になったのでBlock生成
            // BlockMngの場所から生成
            Vector3 position = transform.position;

            // ﾗﾝﾀﾞﾑで高さを変える
            position.y = Random.Range(-4, 4);

            // プレハブを元にBlock生成
            GameObject obj = Instantiate(block, position, Quaternion.identity);

            // ﾌﾞﾛｯｸの情報取得
            Block blockScript = obj.GetComponent<Block>();

            // 速度を計算して設定
            // 基本速度100に、経過時間*10を加える
            float speed = blockScript._speed + (_totalTime * 10);

            blockScript.SetSpeed(-speed);

            // 生成されます
            _cnt++;

            // 偏りを設定する
            if (_cnt % 10 < 3)
            {
                // timerを早めに設定する
                _timer = 0.3f;
            }
            else
            {
                // リセット
                _timer = 1;
            }
        }
    }
}
