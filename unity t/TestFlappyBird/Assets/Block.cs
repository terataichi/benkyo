using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{
    Rigidbody2D _rigidbody;
    public float _speed;

    // Start is called before the first frame update
    void Start()
    {
        // 物理挙動コンポーネートの格納
        _rigidbody = GetComponent<Rigidbody2D>();
        _speed = 100;
    }

    // Update is called once per frame
    void Update()
    {
        Vector2 _position = transform.position;

        _rigidbody.velocity = Vector2.zero;                     // 落下速度を一度リセットする

        _rigidbody.AddForce(new Vector2(-_speed, 0));

        // 壁ﾁｪｯｸ
        if(_position.x < GetLeft())
        {
            Destroy(gameObject);
        }
    }

    // 画面の左下の座標を取得する
    float GetLeft()
    {
        Vector2 min = Camera.main.ViewportToWorldPoint(Vector2.zero);

        return min.x;
    }

    public void SetSpeed(float speed)
    {
        _speed = speed;
    }

}
