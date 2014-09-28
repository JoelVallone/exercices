package queue;

import java.util.ArrayList;

public class Queue<E>{

    private ArrayList<E> q;
    private int maxSize;
    private int usage;
    private int nextIn;
    private int nextOut;
    
    public Queue(int size){
        if(size < 1) maxSize = 8;
        nextIn = 0;
        nextOut = 0;
        usage = 0;
        q<E> = new ArrayList<E>(size);
    }
    
    public synchronized void enqueue(element E){
        try{
            while(usage == maxSize) this.wait;
            q.add(nextIn,e);   
            nextIn = (nextIn + 1) % maxSize;
            usage++;       
            this.notify();
        }catch(InterruptException e){
            e.printStackTrace();
        }
    }
    
    public synchronized E dequeue(){
        E element = null;
        try{
            while(q.size() == 0) this.wait;
            element = q.remove(nextOut)     
            nextOut = (nextOut + 1) % maxSize;
            usage--;
            this.notify();
        }catch(InterruptException e){
            e.printStackTrace();
        }
    }


}
