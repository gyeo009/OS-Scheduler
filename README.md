Implementation of FCFS, SJF, RR, preemptive-SJF scheduler

구현 과제

# SJF - Non-preemption

void schedule()

Task* pickNextTask() 함수만 수정

Ready Queue 내부에서 가장 짧은 remaining_burst를 가진 task를 다음에 실행할 task로 선정

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/239362b2-8706-4193-8ac8-0aa37fbc5b28/62e3a06e-7775-4a4b-9771-642584fec49d/Untitled.png)

# RR - Non-preemption

void schedule()

Task* pickNextTask() 함수만 수정

**timer 를 min(time quantum, running_task->remaining_burst) 로 설정**

// time == timer일 때 scheduling보다 항상 dispatch가 먼저 실행되기 때문에
// 지금 Task가 다시 큐의 맨 뒤로 삽입된 후
// 아래 delete 연산을 사용해 현재 가리키고 있는 Task를 큐에서 삭제
// 결과적으로 큐의 맨 앞에있어서 현재 작업중이었던 Task가 작업 이후 큐의 맨 뒤로 삽입됨

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/239362b2-8706-4193-8ac8-0aa37fbc5b28/eee7aadb-7441-401a-a297-675223196b52/Untitled.png)

# PSJF - Preemptive SJF

void schedule()

Task* pickNextTask()

void add(int arrival_time, char *name, int burst, int remaining_burst) 수정

void schedule()

Task* pickNextTask() 는 non-preemption SJF와 똑같은 구현

add 할때 디스패처 호출 후 다시 스케쥴링 하도록 구현!

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/239362b2-8706-4193-8ac8-0aa37fbc5b28/042ab947-c598-4e5a-83d1-141051e0a887/Untitled.png)
