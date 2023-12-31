import random

#simulation scenario
userChoice = int(input('Select scenario:\n[1]simple, \n[2]moderate, \n[3]crowded, \n[4]overCrowded : \nEnter a chocie <1-4>:'))
if userChoice == 1:
    scenario = 'simple'
elif userChoice==2:
    scenario = 'moderate'
elif userChoice==3:
    scenario = 'crowded'
else:
    scenario = 'overCrowded'
print('Selected scenario is', scenario)


# Define constants for the file format
station_count = {'simple': random.randint(2,3), 'moderate': random.randint(4,7), 'crowded': random.randint(8,10),'overCrowded': random.randint(8,10)}[scenario]
time_between_station = {'simple': random.randint(2,5), 'moderate': random.randint(6,9), 'crowded': random.randint(10,15),'overCrowded': random.randint(16,25)}[scenario]
wbus_count = {'simple': random.randint(1,2), 'moderate': random.randint(3,4), 'crowded': random.randint(4,5),'overCrowded': random.randint(2,3)}[scenario]
mbus_count = {'simple': random.randint(2,3), 'moderate': random.randint(3,5), 'crowded': random.randint(5,7),'overCrowded': random.randint(5,7)}[scenario]
wbus_capacity = {'simple': random.randint(5,10), 'moderate': random.randint(10,15), 'crowded': random.randint(15,20),'overCrowded': random.randint(10,15)}[scenario]
mbus_capacity = {'simple': random.randint(10,15), 'moderate': random.randint(15,20), 'crowded': random.randint(20,30),'overCrowded': random.randint(15,20)}[scenario]
checkup_trips = {'simple': random.randint(1,3), 'moderate': random.randint(4,7), 'crowded': random.randint(8,10),'overCrowded': random.randint(4,6)}[scenario]
wcheckup_duration = {'simple': random.randint(10,20), 'moderate': random.randint(20,25), 'crowded': random.randint(25,35),'overCrowded': random.randint(40,50)}[scenario]
mcheckup_duration = {'simple': random.randint(10,20), 'moderate': random.randint(20,25), 'crowded': random.randint(25,35),'overCrowded': random.randint(40,50)}[scenario]
max_w = random.randint(30,45)
get_on_off_time = random.randint(1,3)
event_count = {'simple': random.randint(30,40), 'moderate': random.randint(50,80), 'crowded': random.randint(100,150),'overCrowded': random.randint(200,400)}[scenario]

#the inter-arrival time (time between successive events)
#depends on the total no. of events to be handled during working hours
#working hours are from 4:00 t0 22:00
from datetime import timedelta
startTime = timedelta(hours=4, minutes=0)   #4:00
endTime = timedelta(hours=22, minutes=0)    #22:00
duration_in_min = (endTime - startTime).seconds/60 #total minutes
max_interArr = int(duration_in_min/event_count)

PERCENT_LEAVE_EVENTS = 5 #percentage of leave events %



# Generate random file content

# Write the file header
with open('random_file.txt', 'w') as f:
    f.write(f'{station_count} {time_between_station}\n')
    f.write(f'{wbus_count} {mbus_count}   \n')
    f.write(f'{wbus_capacity} {mbus_capacity} \n{checkup_trips} {mcheckup_duration} {wcheckup_duration}\n')
    f.write(f'{max_w} {get_on_off_time}\n')
    f.write(f'{event_count}\n')

    NP = [] #normal passengers list (to pick from for leave events)

    event_time = startTime  #4:00
    # Generate and write event lines
    i = 1
    id = 0
    while i <=event_count:

        #first generate random event time
        interArrival_time = {'simple': random.randint(0,10), 'moderate': random.randint(0,7), 'crowded': random.randint(0,5),'overCrowded': random.randint(0,3)}[scenario]
        #if inter-arriv exceeds max_interArr, some passengers may come after 22:00
        if interArrival_time > max_interArr:
            interArrival_time = max_interArr
        event_time += timedelta(minutes=interArrival_time)
        event_hr=int(event_time.seconds/3600)
        event_min = int(event_time.seconds/60)%60

        n = random.randint(1,100)
        if n> PERCENT_LEAVE_EVENTS:
            #Arrival event
            event_type = 'A'
            id +=1
            passenger_type = random.choice(['NP', 'WP', 'SP'])
            src_station = random.randint(1,station_count)
            dst_station = random.randint(1,station_count)
            while dst_station == src_station:
                dst_station = random.randint(1,station_count)
            if passenger_type == 'NP':
                #store a passenger to pick for leave events later
                NP_dic ={}
                NP_dic['ID'] = id
                NP_dic['srcStation'] = src_station
                NP.append(NP_dic)

            f.write(f'{event_type} {passenger_type} {event_hr}{":"}{event_min} {id} {src_station} {dst_station} ')
            if passenger_type == 'SP':
                f.write(f'{random.choice(["aged", "POD", "Pregnant"])}')
            f.write('\n')
        else:
            if NP==[]: #empty list
                i = i-1
                #print('stuck here in leave')
                continue
            #Leave event
            event_type = 'L'
            randomLeavingPassIndex = random.randint(0,len(NP)-1)
            L_id = NP[randomLeavingPassIndex]["ID"]
            src_station = NP[randomLeavingPassIndex]["srcStation"]
            f.write(f'{event_type} {event_hr}{":"}{event_min} {L_id} {src_station}\n')
            del NP[randomLeavingPassIndex] #remove this pass
        i+=1

f.close()
print('Random file generated successfully')
print('The generated file name is random_file.txt')
