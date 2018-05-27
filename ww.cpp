// Assuming we are inputting timestamps which are different for each process
// and transactions input are sorted on the basis of their timestamps

/*
Parth has given a detailed answer. Here I summarize it in a different way.

Assume that Ti requests a lock held by Tj. The following table summarizes the actions taken for wait-die and wound-wait scheme:

                           wait-die         wound-wait
Ti is younger than Tj      Ti dies          Ti waits
Ti is older than Tj        Ti waits         Tj aborts
Both schemes prefer older transactions with an older timestamp.
*/
// transaction id should be of one char (0..9)
// locked var should be from A to Z only
// a waiting transaction cant request a variable
// a waiting transaction will not release the variables it has locked
// the transaction which will go to wait first will be given priority to wake first
// if a transaction is aborted then it is not longer my responsibility to start it again


//dont append same to the waiting list again
//print restart statement
//

#include <bits/stdc++.h>

using namespace std;

typedef struct transx
{
  int id;
  int timeStamp;
  // State status = waiting;       // 0 - waiting, 1 - active, 2 - finished
  vector<char> locked_var;
} Transaction;

typedef struct vars
{
  // char c;
  int allotedTo;
} Variables;

std::vector<Transaction> allTransactions;
std::vector<int> waitingTransactions;
enum  State { waiting,active,finished };
int allVars[26]={0};



int findTimestamp(int transactionId){
  for (int i = 0; i < allTransactions.size(); ++i)
  {
    if (allTransactions[i].id ==transactionId)
    {
      return allTransactions[i].timeStamp;
    }
    else
      continue;
  }
}

void Wait(int transactionId){
  waitingTransactions.push_back(transactionId);
  return;
}

int findTransactionIndex(int transactionId){
  for (int i = 0; i < allTransactions.size(); ++i)
  {
    if (allTransactions[i].id==transactionId)
    {
      return i;
    }
    else{
      continue;
    }
  }
  return -1;
}

int deallocate(int transactionId){
  int tid = findTransactionIndex(transactionId);
  if (tid==-1)
  {
    return -1;
  }
  for (int j = 0; j < allTransactions[tid].locked_var.size() ; ++j)
  {
    allVars[allTransactions[tid].locked_var[j] - 65]=0;
  }
  allTransactions.erase(allTransactions.begin()+tid);
  return tid;
}

void Preempt(int transactionId){
  deallocate(transactionId);
  return;
}





void checkWaitingQueue(){
  int j;
  for (int i :waitingTransactions)
  {
    int id_ = findTransactionIndex(i);
    // cout<<i<<endl;
    for ( j= 0; j < allTransactions[id_].locked_var.size(); ++j)
    {
      if(allVars[allTransactions[id_].locked_var[j]-65]==0 || allVars[allTransactions[id_].locked_var[j]-65]==i){
        // cout<<allTransactions[id_].locked_var[j]<<endl;
        // cout<<allVars[allTransactions[id_].locked_var[j]-65]<<endl;
        continue;
      }
      else{
        break;
      }
    }
    if (j == allTransactions[id_].locked_var.size())
    {
      for ( j= 0; j < allTransactions[id_].locked_var.size(); ++j)
      {
        allVars[allTransactions[id_].locked_var[j]-65]=i;
      }
      std::vector<int>::iterator it = std::find(waitingTransactions.begin(), waitingTransactions.end(), i);
      waitingTransactions.erase(it);
      it--;
    }
    else{
      continue;
    }
  }
}

int main()
{
  // int length;
  int transactionId,time_=0;
  char readVar;
  
  string input;
  
  while(1){
    time_++;
    cin>>input;
    // length = strlen(input);
    if (input=="Done")
    {
      break;
    }
    else if (input[0]=='b')
    {
      Transaction* newTransaction = new Transaction;
      newTransaction->id = int(input[1])-48;
      newTransaction->timeStamp = time_;
      allTransactions.push_back(*newTransaction);
      cout<<"New Transaction started id: "<<newTransaction->id<<endl;
    }
    else if (input[0]=='r')
    {
      transactionId = int(input[1])-48;
      readVar = input[3];
      if (allVars[readVar - 65]==0 )
      {
        allVars[readVar - 65] = transactionId;
        int tid = findTransactionIndex(transactionId);
        allTransactions[tid].locked_var.push_back(readVar);
        cout<<"Transaction id: "<<transactionId<<" aquired variable "<<readVar<<endl;
      }
      else if (allVars[readVar - 65] ==transactionId)
      {
        // do nothing
        cout<<"Transaction id: "<<transactionId<< " already have the lock of the requested variable: "<<readVar<<endl;
      }
      else if (allVars[readVar - 65] !=transactionId)
      {
        int newTransxTS=findTimestamp(transactionId);
        int oldTransxTS=findTimestamp(allVars[readVar - 65]);
        if (newTransxTS > oldTransxTS)
        {
          // here insert the var into the locked_var list
          int tid = findTransactionIndex(transactionId);
          allTransactions[tid].locked_var.push_back(readVar);
          Wait(transactionId);
          cout<<"Transaction id: "<<transactionId<<" is added to waiting list\n";
        }
        else if (newTransxTS < oldTransxTS)
        {
          cout<<"Preempted transaction id: "<<allVars[readVar - 65]<<endl;
          Preempt(allVars[readVar - 65]);
          allVars[readVar - 65] = transactionId;
          int tid = findTransactionIndex(transactionId);
          allTransactions[tid].locked_var.push_back(readVar);
          checkWaitingQueue();
          
        }
      }
    }
    else if (input[0]=='w')
    {
      transactionId = int(input[1])-48;
      readVar = input[3];
      if (allVars[readVar - 65]==0 )
      {
        allVars[readVar - 65] = transactionId;
        int tid = findTransactionIndex(transactionId);
        allTransactions[tid].locked_var.push_back(readVar);
        cout<<"Transaction id: "<<transactionId<<" aquired variable "<<readVar<<endl;
      }
      else if (allVars[readVar - 65] ==transactionId)
      {
        // do nothing
        cout<<"Transaction id: "<<transactionId<< " already have the lock of the requested variable: "<<readVar<<endl;
      }
      else if (allVars[readVar - 65] !=transactionId)
      {
        int newTransxTS=findTimestamp(transactionId);
        int oldTransxTS=findTimestamp(allVars[readVar - 65]);
        if (newTransxTS > oldTransxTS)
        {
          int tid = findTransactionIndex(transactionId);
          allTransactions[tid].locked_var.push_back(readVar);
          Wait(transactionId);
          cout<<"Transaction id: "<<transactionId<<" is added to waiting list\n";
        }
        else if (newTransxTS < oldTransxTS)
        {
          cout<<"Preempted transaction id: "<<allVars[readVar - 65]<<endl;
          Preempt(allVars[readVar - 65]);

          allVars[readVar - 65] = transactionId;
          int tid = findTransactionIndex(transactionId);
          allTransactions[tid].locked_var.push_back(readVar);
          checkWaitingQueue();
          
        }
      }
    }
    else if (input[0]=='c')
    {
      transactionId = input[1]-48;
      int temp = deallocate(transactionId);
      if (temp==-1)
      {
        continue;
      }
      checkWaitingQueue();
      cout<<"Completed transaction id: "<<transactionId<<endl;
    }
  }
 return 0;
}
