using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// ｼｰﾝ以降に必要
using UnityEngine.SceneManagement;

public class GameMng : MonoBehaviour
{
    // 状態定義
    enum State
    {
        ALIVE,
        DEAD
    }

    // 変数の定義
    int _score;
    static int _highScore = 0;
    State _state;


    // Start is called before the first frame update
    void Start()
    {
        // 初期化
        _score = 0;
        _state = State.ALIVE;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetGameOver()
    {
        _state = State.DEAD;
    }

    private void OnGUI()
    {
        // ｽｺｱの描画
        DrawScore();

        if (_state == State.DEAD)
        {
            // 画面の中心座標の計算
            float tempX = Screen.width / 2;
            float tempY = Screen.height / 2;

            DrawGameOver(tempX, tempY);

            if (DrawRetryButton(tempX, tempY) || Input.GetKeyDown(KeyCode.Space))
            {
                // trueでリセットする
                SceneManager.LoadScene("MainScene");
            }
        }
    }

    void DrawScore()
    {
        // 文字を大きくする
        GUI.skin.label.fontSize = 32;

        // 左揃えに設定
        GUI.skin.label.alignment = TextAnchor.MiddleLeft;

        Rect score = new Rect(0, 0, 400, 100);
        Rect highScore = new Rect(Screen.width / 2 - 60, 0, 400, 100);

        GUI.Label(score, string.Format("score:{0}", _score));
        GUI.Label(highScore, string.Format("HighScore:{0}", _highScore));
    }

    void DrawGameOver(float CenterX, float CenterY)
    {
        // 中央揃えに設定
        GUI.skin.label.alignment = TextAnchor.MiddleCenter;

        float w = 400;
        float h = 100;

        Rect position = new Rect(CenterX - w / 2, CenterY - h / 2, w, h);
        GUI.Label(position, "GAME OVER");
    }

    bool DrawRetryButton(float CenterX, float CenterY)
    {
        float ofsY = 40;
        float w = 100;
        float h = 64;

        Rect rect = new Rect(CenterX - w / 2, CenterY + ofsY, w, h);

        if (GUI.Button(rect, "RETRY"))
        {
            // ボタンを押した
            return true;
        }

        return false;
    }

    public void AddScore()
    {
        if (_state == State.ALIVE)
        {
            // ｽｺｱ上昇
            _score++;

            // ﾊｲｽｺｱ更新
            if (_score > _highScore)
            {
                _highScore = _score;
            }
        }
    }
}
