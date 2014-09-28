package queue;

public class Bench{

    public static void main(String args[]){
        //Initialize parameters
        int nbConsumer = 1;
        int nbProducer = 1;
        int nbExchange = 2;
        if(args.size() > 0) nbConsumer = getInteger(args[0]);
        if(args.size() > 1) nbProducer = getInteger(args[1]);
        if(args.size() > 2) nbExchange = getInteger(args[2]);
        
        //Thread safe queue instantiation
        Queue<Integer> q = new Queue<Integer>(nbExchange);
        
        //Instantiate threads
        Runnable Consumers[] = new Runnable[nbConsumer];
        Runnable Producers[] = new Runnable[nbProducer];
        Thread TConsumers[] = new Thread[nbConsumer];
        Thread TProducers[] = new Thread[nbProducer];
        for(int i = 0; i < nbConsumer && i < nbProducer; i++){
            if(i < nbConsumer){
                Consumers[i] = new Consumers<Integer>(q,nbExchange);
                TConsumer[i] = new Thread(Consumers[i]);
            }
            if(i < nbProducer){
                Producers[i] = new Producers<Integer>(q,nbExchange);
                TProducers[i] = new Thread(Producers[i] );
            }
        }
        
        //Start Threads and wait their end
        for(int i = 0; i < nbConsumer; i++){
            TConsumer[i].join();
        }
        
        System.out.println("Main : End of process");
    }

    
    private Consumer<E> implements Runnable{
        private queue<E> q;
        private nbConsume
        public Consumer(queue<E> q, int nbConsume){
            this.q = q;
            this.nbConsume = nbConsume;
        }
        
        public void Run(){
            for(int i = 0; i < nbConsume ; i++){
                System.out.println("Thread " + this.getId() 
                    + ": took " + q.dequeue(i);
            }
        }
    }
    
    private Producer implements Runnable{
        private queue<E> q;
        private nbProduce
        public Producer(queue<E> q, int nbProduce){
            this.q = q;
            this.nbProduce = nbProduce;
        }
        
        public void Run(){
            for(int i = 0; i < nbProduce ; i++){
                q.enqueue(i);
                System.out.println("Thread " + this.getId() + ": added " + i);
            }
        }
    
    }
}
