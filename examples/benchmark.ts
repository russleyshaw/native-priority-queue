const NodePQ = require("priorityqueuejs");
import { PriorityQueue as NativePQ } from "../";

interface Person {
    name: string;
    age: number;
}

function getRandomInt(min: number, max: number) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive
}

// Simulate heavy priority calculation
function takeALongTime(n: number): number {
    let a = 0;
    for (let i = 0; i < 10000; i++) {
        a++;
    }
    return n;
}

function benchmark(name: string, func: () => void) {
    console.time(name);
    func();
    console.timeEnd(name);
}

// Set up queues
const nodeq = new NodePQ((a: Person, b: Person) => {
    return a.age - b.age;
});
const nativeq = new NativePQ<Person>(p => p.age);

console.log("Building test data...");

// Set up test data
const ENQUEUE_SIZE = 4000000;
const people: Person[] = [];
for (let i = 0; i < ENQUEUE_SIZE; i++) {
    people.push({
        name: `person-${i}`,
        age: getRandomInt(0, ENQUEUE_SIZE)
    });
}

console.log("Built test data! Size: ", ENQUEUE_SIZE);

benchmark("Enqueuing NodePQ", () => {
    for (const person of people) {
        nodeq.enq(person);
    }
});

benchmark("Enqueuing NativePQ", () => {
    for (const person of people) {
        nativeq.push(person);
    }
});

benchmark("Popping NodePQ", () => {
    for (const person of people) {
        nodeq.deq();
    }
});

benchmark("Popping NativePQ", () => {
    for (const person of people) {
        nativeq.pop();
    }
});
