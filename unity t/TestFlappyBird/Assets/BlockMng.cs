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

    void Start()
    {
        _timer = 0;
        _totalTime = 0;
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

            // プレハブを元にBlock生成
            GameObject obj = Instantiate(block, position, Quaternion.identity);

            // ﾌﾞﾛｯｸの情報取得
            Block blockScript = obj.GetComponent<Block>();

            // 速度を計算して設定
            // 基本速度100に、経過時間*10を加える
            float speed = blockScript._speed + (_totalTime * 10);

            blockScript.SetSpeed(-speed);

            // リセット
            _timer += 1;
        }
    }
}
