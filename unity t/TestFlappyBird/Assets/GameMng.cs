using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameMng : MonoBehaviour
{
    // 

    // 変数の定義
    int _score;

    // Start is called before the first frame update
    void Start()
    {
        // 初期化
        _score = 0;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // FixedUpdate
    private void FixedUpdate()
    {
        // ｽｺｱ上昇
        _score += 1;
    }

    private void OnGUI()
    {
        // ｽｺｱの描画
        DrawScore();
    }

    void DrawScore()
    {
        // 文字を大きくする
        GUI.skin.label.fontSize = 32;

        // 左揃えに設定
        GUI.skin.label.alignment = TextAnchor.MiddleLeft;

        Rect position = new Rect(8, 8, 400, 100);

        GUI.Label(position, string.Format("score;{0}", _score));
    }
}
