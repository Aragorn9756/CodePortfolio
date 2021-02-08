using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance = null;
    public GameObject player;
    public Transform knifePos;
    public Transform outletPos;
    public Transform playerPos;
    public GameObject baby;
    public bool hasKnife = false;
    public Timer timerScript;
    public Text menuText;

    private Baby babyScript;
    private Save save;

    void Start()
    {
        //instantiate singleton
        if (Instance == null)
        {
            Instance = this;
        } else if (Instance != this) {
            Destroy(gameObject);
        }

        babyScript = baby.GetComponent<Baby>();
        save = LoadSave();

        //plays intro
        StartCoroutine(OpeningWindow());
    }

    // Update is called once per frame
    void Update()
    {
        //if start button is pressed, exit game
        if (OVRInput.GetUp(OVRInput.Button.Start))
        {
            Debug.Log("Start Button Pressed");
            Application.Quit();
        }
       
        //if baby doesn't have the knife, it goes for the knife
        if (!hasKnife)
        {
            babyScript.target = knifePos;
        } else
        {
            babyScript.target = outletPos;
        }
    }

    public void GameOver ()
    {
        if (timerScript.gameOver == false) //if you lost
        {
            //set the text to you lose.
            timerScript.GameLost();
            save.losses += 1;
        } else
        {
            save.wins += 1;
        }
        //Save the game
        SaveGame();

        //start a coroutine that waits for 5 seconds before closing the game
        StartCoroutine(Exit());
    }
    
    IEnumerator Exit ()
    {
        yield return new WaitForSecondsRealtime(5);
        Debug.Log("Just about to quit");
        Application.Quit();
    }

    private void SaveGame()
    {
        BinaryFormatter bf = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/gamesave.save");
        bf.Serialize(file, save);
        file.Close();
    }

    private Save LoadSave()
    {
        if (File.Exists(Application.persistentDataPath + "/gamesave.save"))
        {
            BinaryFormatter bf = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/gamesave.save", FileMode.Open);
            save = (Save)bf.Deserialize(file);
            file.Close();
        } else
        {
            Debug.Log("No data loaded");
            save = new Save();
        }

        return save;
    }

    //the ui window with the Game Title, win loss Record, and how to exit the game
    IEnumerator OpeningWindow()
    {
        //activate the canvas the text is a child of.
        timerScript.enabled = false;
        babyScript.enabled = false;

        menuText.text = "Welcome to Parenting Simulator!";
        yield return new WaitForSecondsRealtime(5);
        menuText.text = "Keep your baby from hurting itself until the timer runs out.";
        yield return new WaitForSecondsRealtime(5);
        menuText.text = "To exit the game, press the start button at any time.";
        yield return new WaitForSecondsRealtime(5);
        menuText.text = "Your current stats are " + save.wins + " win(s) and " + save.losses + " loss(es).";
        yield return new WaitForSecondsRealtime(5);
        menuText.text = "Ready?";
        yield return new WaitForSecondsRealtime(3);
        menuText.text = "3";
        yield return new WaitForSecondsRealtime(1);
        menuText.text = "2";
        yield return new WaitForSecondsRealtime(1);
        menuText.text = "1";
        yield return new WaitForSecondsRealtime(1);
        menuText.text = "GO!";
        yield return new WaitForSecondsRealtime(1);

        timerScript.enabled = true;
        babyScript.enabled = true;
    }
}
