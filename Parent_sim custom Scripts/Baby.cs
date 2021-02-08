using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Baby : MonoBehaviour
{
    [HideInInspector]
    public Transform target;
    public Transform knifeTrans;
    public bool knifeGrab = false;

    private NavMeshAgent agent;
    private bool grabbed = false;
    private OVRGrabbable grabScript;
    private Rigidbody rb;

    void Start()
    {
        agent = GetComponent<NavMeshAgent>();
        grabScript = this.gameObject.GetComponent<OVRGrabbable>();
        rb = this.gameObject.GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(grabScript.isGrabbed);
        //move to current target if not grabbed
        if (grabScript.isGrabbed == false)
        {
            agent.destination = target.position;
            Debug.Log(agent.pathStatus);
        }

        if (knifeGrab)
        {
            knifeTrans.position = this.transform.position;
        } //else 

        // if grabbed...
        if (grabScript.isGrabbed)
        {
            agent.enabled = false;
            //make sure that grabbed is set to true
            if (!grabbed)
            {
                grabbed = true;
                //disable rigidbody temporarily to stop the rigidbody from interacting with the player
                rb.Sleep();

                //if holding knife, drop it
                if (GameManager.Instance.hasKnife == true)
                {
                    knifeGrab = false;

                    //unfreeze knifes position and reenable the collider
                    knifeTrans.gameObject.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.None;
                    
                    
                    StartCoroutine(KnifeDrop());
                    GameManager.Instance.hasKnife = false;
                }
                
            }
        }//if not grabbed right now, but grabbed is true, reset it.
        else if (!grabScript.isGrabbed && grabbed)
        {
            grabbed = false;
            rb.WakeUp();
            agent.enabled = true;
        }
    }

    void OnCollisionEnter (Collision coll)
    {
        Debug.Log(coll.gameObject.name);
        GameObject tempObject = coll.gameObject;
        if (tempObject.name == "knife")
        {
            knifeGrab = true;
            Rigidbody tempRigid = coll.gameObject.GetComponent<Rigidbody>();

            //disable collider
            tempObject.GetComponent<BoxCollider>().enabled = false;

            //freeze position of knife.
            tempRigid.constraints = RigidbodyConstraints.FreezePosition; //to unfreeze, tempRigid.constraints = RigidbodyConstraints.None
            GameManager.Instance.hasKnife = true;
        }

        //if has knife and reaches outlet, game over.
        if (GameManager.Instance.hasKnife && coll.gameObject.name == "Outlet")
        {
            GameManager.Instance.GameOver();
        }
    }

    IEnumerator KnifeDrop()
    {
        knifeTrans.gameObject.GetComponent<Rigidbody>().Sleep();

        yield return new WaitForSeconds(0.5f);
        Debug.Log("Got to Knife Drop");

        knifeTrans.gameObject.GetComponent<Rigidbody>().WakeUp();
        knifeTrans.gameObject.GetComponent<BoxCollider>().enabled = true;
        knifeTrans.position +=  new Vector3(.2f, 0);
        //if below the floor, bring back up.
        if (knifeTrans.position.y < 0)
        {
            knifeTrans.position -= new Vector3(0, knifeTrans.position.y + .02f);
        }
    }
}
