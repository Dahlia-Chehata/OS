#include <pthread.h>
#include "caltrain.h"

void
station_init(struct station *station)
{

    pthread_cond_init(&(station->trainArrivalSignal_cond),NULL);
    pthread_cond_init(&(station->trainFull_cond),NULL);
    pthread_cond_init(&(station->noAvailableSeat_cond),NULL);
    pthread_mutex_init(&(station->mutex),NULL);
    station->onTrain_passengers=0;
    station->waiting_passengers=0;
    station->seats_available =0;

}
/**
 - When a train arrives in the station and has opened its doors, it invokes this function
*/
void
station_load_train(struct station *station, int count)
{

    if (!count || ! station->waiting_passengers) return; //no empty seats or no waiting passengers,the train immediately
    pthread_mutex_lock(&(station->mutex));
    /*
    enter critical section
    */
    station->seats_available=count;
    while (station->waiting_passengers&& station->seats_available)
    {
        pthread_cond_broadcast(&(station->trainArrivalSignal_cond)); //informs all threads of passengers of the train arrival
        pthread_cond_wait(&(station->noAvailableSeat_cond),&(station->mutex)); //wait for the no available seat condition
    }
    //initializing again for next train/thread
    station->seats_available=0;
    /* leave critical section
    */
    pthread_mutex_unlock(&(station->mutex));
}
/**
-When a passenger robot arrives in a station ,it invokes the function
-only returns when a train is in station and there is a seat available for passenger
*/

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&(station->mutex));
    /*enter critical section
    */
    station->waiting_passengers++; //add a waiting passenger for whom a train will be loaded
    while (station->seats_available == station->onTrain_passengers)
    {
        pthread_cond_wait(&(station->trainArrivalSignal_cond), &(station->mutex));
    }
    station->waiting_passengers--; //passenger is removed from the waiting list
    station->onTrain_passengers++; // the passenger is added to the to boardedlist
    /*leave critical section
    */
    pthread_mutex_unlock(&(station->mutex));
}
/**
-notify the train to be on board,all passengers (within the available size in train) are seated
*/
void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&(station->mutex));
    /*enter critical section
    */
    station->seats_available--; //decreasing the number of empty seats
    station->onTrain_passengers--; //the passenger will be on board state and no longer on train state
    if (!station->onTrain_passengers || !station->seats_available)
        pthread_cond_broadcast(&(station->noAvailableSeat_cond)); //informs all thread that train is full
    /*leave critical section
    */
    pthread_mutex_unlock(&(station->mutex));

}
