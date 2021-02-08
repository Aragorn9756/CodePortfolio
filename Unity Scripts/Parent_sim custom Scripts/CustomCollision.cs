using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomCollision : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("hit" + other.name);
        if (other.name == "grabbedChair")
        {
            other.transform.position = transform.position;
            other.transform.parent = transform.parent;
            Debug.Log("Snapped " + other.name + " to " + this.name);
        }
    }
}
