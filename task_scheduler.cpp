
#include<iostream>
#include<string>
using namespace std;

/* Class to Store Details of a particular Task */
class Task{
    
    string description; // to give description
    string activity;    // to store activity name
    int priority;       // to store priority Assignments->4 Exams->3 Projects->2 Extracurricular->1
    
public:
    
    /* Constructors and Destructors */
    Task(){
        description = "empty";
        activity = "empty";
        priority = -1;
    }
    
    Task(Task &t){
        this->description = t.getDescription();
        this->activity = t.getActivity();
        this->priority = t.getPriority();
    }
    
    ~Task(){}

    /* Getters and Setters */
    string getDescription(){ return description; }
    string getActivity(){ return activity; }
    int getPriority(){ return priority; }
    
    void setDescription(string description){ this->description = description; }
    void setActivity(string activity){ this->activity = activity; }
    void setPriority(int priority){ this->priority = priority; }
    
    /* Utility Functions */
    void inputTask(){
        int p;
        cout<<"Enter Task priority:"<<endl;
        cout<<"Enter 4 for Assignments"<<endl;
        cout<<"Enter 3 for Exams"<<endl;
        cout<<"Enter 2 for Projects"<<endl;
        cout<<"Enter 1 for Extracurricular"<<endl;
        
        while (1) {
            cin>>p;
            if(p==4 || p==3 || p==2 || p==1){
                setPriority(p);
                setActivityUsingPriority(p);
                break;
            }else{
                cout<<"Oops!...This is not a valid task priority!"<<endl;
            }
        }
        
        cout<<"Enter task description"<<endl;
        cin.ignore();
        getline(cin, description);
    }
    
    void setActivityUsingPriority(int priority){
        if (priority == 4) {
            setActivity("Assignments");
        } else if (priority == 3) {
            setActivity("Exams");
        } else if (priority == 2) {
            setActivity("Projects");
        } else {
            setActivity("Extracurricular");
        }
    }
    
    void printTask(){
        cout<<"****************************************"<<endl;
        cout<<"Description : "<<this->description<<endl;
        cout<<"Activity    : "<<this->activity<<endl;
        cout<<"****************************************"<<endl;
    }
};

/*Class to store To-Do List*/
class TaskList{
    
    string Student;
    Task* tasks;
    int maxTasks;
    int numberOfTasks;
    
public:
    /* Constructors and Destructors */
    TaskList(){
        Student = "empty";
        tasks = NULL;
    }
    
    TaskList(int maxTasks, string Student){
        this->maxTasks = maxTasks;
        numberOfTasks = 0;
        tasks = new Task[maxTasks];
        this->Student = Student;
    }
    
    ~TaskList(){
        delete[] tasks;
    }
    
    /*Getters and Setters*/
    string getStudent(){ return Student; }
    int getPendingTasks(){ return numberOfTasks; }
    int getMaxTasks(){ return maxTasks; }
    
    void setStudent(string Student){ this->Student = Student; }
    void setMaxTasks(int maxTasks){ this->maxTasks = maxTasks; }
    
    /*Functions for Implementing Priority Queue */
    bool LeafNode(int position){
        return (2 * position + 1) > numberOfTasks;
    }
    
    int rightChildNode(int position){
        return (2 * position + 2);
    }
    
    int leftChildNode(int position){
        return (2 * position + 1);
    }
    
    int parent(int position){
        return (position - 1) / 2;
    }
    
    /*Function to add task in To-Do List*/
    void addTask(const Task& task){
        if(numberOfTasks == maxTasks)
            cout<<"Task list is full (OVERFLOW)"<<endl;
        else{
            numberOfTasks++;
            tasks[numberOfTasks - 1] = task;
            shiftUp(numberOfTasks - 1);
        }
    }
    
    /*Function to Remove Task from To-Do List*/
    Task removeTask(){
        Task priority;
        priority = extractMax();
        return priority;
    }
    
    /* Utility functions to help creation of heap */
    void shiftUp(int position){
        while(position >= 0 && tasks[parent(position)].getPriority() < tasks[position].getPriority()){
            Task temp = tasks[position];
            tasks[position] = tasks[parent(position)];
            tasks[parent(position)] = temp;
            position = parent(position);
        }
    }
    
    void shiftDown(int position){
        int maxIndex = position;
        int l = leftChildNode(position);
        int r = rightChildNode(position);
        
        if(l < numberOfTasks && tasks[l].getPriority() > tasks[maxIndex].getPriority())
            maxIndex = l;
        
        if(r < numberOfTasks && tasks[r].getPriority() > tasks[maxIndex].getPriority())
            maxIndex = r;
        
        if(position != maxIndex){
            Task temp = tasks[position];
            tasks[position] = tasks[maxIndex];
            tasks[maxIndex] = temp;
            shiftDown(maxIndex);
        }
    }
    
    Task extractMax(){
        if(numberOfTasks == 0){
            Task empty;
            return empty;
        } else {
            Task result = tasks[0];
            tasks[0] = tasks[numberOfTasks - 1];
            numberOfTasks--;
            shiftDown(0);
            return result;
        }
    }
    
    /* To get task with current priority */
    Task currentPriority(){
        if(numberOfTasks == 0){
            Task empty;
            return empty;
        } else {
            return tasks[0];
        }
    }

    /* To get task of next priority */
    Task nextPriority(){
        if(numberOfTasks == 0){
            Task empty;
            return empty;
        } else {
            Task result1 = tasks[leftChildNode(0)];
            Task result2 = tasks[rightChildNode(0)];
            return (result2.getPriority() >= result1.getPriority()) ? result2 : result1;
        }
    }
    
    /* To print tasks in order of priority */
    void printTasks(){
        Task* temp = new Task[numberOfTasks];
        Task* priority = new Task[numberOfTasks];
        int i = 0, j = numberOfTasks;
        
        for(i = 0; i < j; i++)
            temp[i] = tasks[i];
        
        for(i = 0; i < j; i++)
            priority[i] = extractMax();
        
        cout<<"------------------------------------------------------------"<<endl;
        cout<<"PENDING TASKS"<<endl;
        for(i = 0; i < j; i++){
            priority[i].printTask();
            tasks[i] = temp[i];
        }
        cout<<"------------------------------------------------------------"<<endl;
        numberOfTasks = j;
        delete[] temp;
        delete[] priority;
    }
};


int main(){
    
    int maxTasks;
    string Student;
    
    cout<<"Enter the maximum number of tasks"<<endl;
    cin>>maxTasks;
    
    cout<<"Enter the name of the student"<<endl;
    cin.ignore();   //ignores a specified no.of characters until you reach the given character
    getline(cin, Student);
    
    TaskList taskList(maxTasks, Student);
    Task task;
    
    while(1){
        
        cout<<"-------------------------------------------------------------------------------"<<endl;
        cout<<"Press 1 to add New Task"<<endl;
        cout<<"Press 2 to complete highest Priority Task"<<endl;
        cout<<"Press 3 to see current Priority Task"<<endl;
        cout<<"Press 4 to see next Priority Task"<<endl;
        cout<<"Press 5 to display All Pending Tasks"<<endl;
        cout<<"Press 6 to Exit from program"<<endl;
        
        int choice;
        cout<<"Enter your choice"<<endl;
        cin>>choice;
        
        switch (choice) {
            case 1:
                task.inputTask();
                taskList.addTask(task);
                break;
             
            case 2:
                task = taskList.removeTask();
                if(task.getPriority() != -1){
                    task.printTask();
                    cout<<"TASK COMPLETED"<<endl;
                } else {
                    cout<<"No tasks pending"<<endl;
                }
                break;
                
            case 3:
                task = taskList.currentPriority();
                if(task.getPriority() != -1){
                    task.printTask();
                    cout<<"CURRENT PRIORITY TASK"<<endl;
                } else {
                    cout<<"No tasks pending"<<endl;
                }
                break;
    
            case 4:
                task = taskList.nextPriority();
                if(task.getPriority() != -1){
                    task.printTask();
                    cout<<"NEXT PRIORITY TASK"<<endl;
                } else {
                    cout<<"Only one task pending"<<endl;
                }
                break;
                
            case 5:
                taskList.printTasks();
                break;
                
            case 6:
                return 0;
                
            default:
                break;
        }
    }
    
    return 0;
}
