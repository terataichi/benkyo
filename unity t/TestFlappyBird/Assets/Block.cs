using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{
    Rigidbody2D _rigidbody;
    public float _speed;
    public bool _scoreFlg;

    static Bard _bard = null;                      // ﾌﾟﾚｲﾔｰの情報取得用

    static GameMng _gameMng = null;                // ｹﾞｰﾑﾏﾈｰｼﾞｬｰの情報取得用  

    // Start is called before the first frame update
    void Start()
    {
        // 物理挙動コンポーネートの格納
        _rigidbody = GetComponent<Rigidbody2D>();
        _speed = 100;
        _scoreFlg = false;

        if (_bard == null)
        {
            _bard = GameObject.Find("Bard").GetComponent<Bard>();
        }
        if (_gameMng == null)
        {
            _gameMng = GameObject.Find("GameMng").GetComponent<GameMng>();
        }

        //_bard = bardObj.GetComponent<Bard>();
        //_gameMng = gameMng.GetComponent<GameMng>();
    }

    // Update is called once per frame
    void Update()
    {
        float x = transform.position.x;

        _rigidbody.velocity = Vector2.zero;                     // 落下速度を一度リセットする

        _rigidbody.AddForce(new Vector2(-_speed, 0));

        // 壁ﾁｪｯｸ
        if(x < GetLeft())
        {
            Destroy(gameObject);
        }

        if(IsAddScore())
        {
            _gameMng.AddScore();
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

    // スコアを加算していいかどうか
    public bool IsAddScore()
    {
        float tempX = transform.position.x;
        // player > block
        if (_bard.Pos().x > tempX && !_scoreFlg)
        {
            // 一回だけ加算をしたいからトリガーをつけた
            _scoreFlg = true;
            return true;
        }

        return false;
    }
}
