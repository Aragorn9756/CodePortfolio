using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    public Text text;
    public string winText;
    public string loseText;
    public float timeLeft;
    public bool gameOver = false;
    void Start()
    {
        text = GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!gameOver) {
            timeLeft -= Time.deltaTime;
            text.text = "Time Left: " + Mathf.Ceil(timeLeft).ToString();

            //if times up
            if (timeLeft <= 0)
            {
                text.text = winText;
                gameOver = true;
                GameManager.Instance.GameOver();
            }
        }
        

    }

    public void GameLost ()
    {
        text.text = loseText;
        gameOver = true;
    }
}
