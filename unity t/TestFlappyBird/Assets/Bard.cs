using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// ﾌﾟﾚｲﾔｰ
public class Bard : MonoBehaviour
{
    [SerializeField]

    float JUMP_VELOCITY;                      // ｼﾞｬﾝﾌﾟ力

    Rigidbody2D _rigidbody;                          // 物理挙動ｺﾝﾎﾟｰﾈﾝﾄ保持用

    // 処理開始
    void Start()
    {
        _rigidbody = GetComponent<Rigidbody2D>();    // 物理挙動ｺﾝﾎﾟｰﾈﾝﾄ取得
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            _rigidbody.velocity = Vector2.zero;                     // 落下速度を一度リセットする

            _rigidbody.AddForce(new Vector2(0, JUMP_VELOCITY));     // 飛びます
        }
    }

    private void FixedUpdate()
    {
        // 座標の取得
        Vector3 position = transform.position;

        // 画面外に出ないようにする
        float y = transform.position.y;

        if(y > GetTop())
        {
            _rigidbody.velocity = Vector2.zero;     // 速度リセット
            position.y = GetTop();                  // 押し戻しする
        }

        if(y < GetBottom())
        {
            _rigidbody.velocity = Vector2.zero;                         // 速度リセット
            _rigidbody.AddForce(new Vector2(0, JUMP_VELOCITY));         // 下に落ちたら自動ｼﾞｬﾝﾌﾟ
            position.y = GetBottom();                                   // 押し戻しする
        }

        transform.position = position;
    }

    // 画面の上を取得して返す
    float GetTop()
    {
        Vector2 max = Camera.main.ViewportToWorldPoint(Vector2.one);

        return max.y;
    }

    // 画面の下を取得して返す
    float GetBottom()
    {
        Vector2 min = Camera.main.ViewportToWorldPoint(Vector2.zero);

        return min.y;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        // トリガーがオンになったら衝突してるのでオブジェクトを消す
        Destroy(gameObject);
    }

}
