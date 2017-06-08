﻿using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.Threading;
using System.IO.Ports;
using System.Collections;

public class menu : MonoBehaviour {

    private bool space;
    public SerialPort stream = new SerialPort("/dev/ttyACM0", 9600);
    private int input;

    void Start(){
        space = false;  
        stream.ReadTimeout = 20;
        stream.Open();
    }

    // Update is called once per frame
    void Update(){
        scanKeys();
        readSerialData();
       //Thread.Sleep(200);
    }

    void scanKeys(){
        if(Input.GetKeyUp(KeyCode.LeftArrow)){
            int MyInt = 1;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }
        
        if(Input.GetKeyUp(KeyCode.RightArrow)){
            int MyInt = 2;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }

        if(Input.GetKeyUp(KeyCode.A)){
            int MyInt = 97;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }
        if(Input.GetKeyUp(KeyCode.B)){
            int MyInt = 98;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }
        if(Input.GetKeyUp(KeyCode.C)){
            int MyInt = 99;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }
        if(Input.GetKeyUp(KeyCode.D)){
            int MyInt = 100;
            byte[] b = BitConverter.GetBytes(MyInt);
            stream.Write(b,0,4);
        }

    }  

    void readSerialData(){
        try{
            input = Int32.Parse(stream.ReadLine());

            switch(input){
                case 5252:
                    print("Steady");
                break;
                case 5250:
                    print("Up");
                break;
                case 5254:
                    print("Down");
                break;
                case 5052:
                    print("Left");
                break;
                case 5452:
                    print("Right");
                break;
                case 5256:
                    print("Press");
                break; 
            }
        }
        catch (TimeoutException){}
    }
}