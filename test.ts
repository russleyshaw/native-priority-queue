import { PriorityQueue } from "./";

interface Person {
  name: string;
  age: number;
}

function seperate() {
  console.log("==================================================");
}

function showMeta<T>(pq: PriorityQueue<T>) {
  seperate();
  console.log("Size: ", pq.size());
  console.log("Empty: ", pq.empty());
  console.log("Top: ", pq.top());
}

function pushValue<T>(pq: PriorityQueue<T>, val: T) {
  seperate();
  console.log("Pushing: ", val);
  pq.push(val);
}

const pq = new PriorityQueue<Person>();
showMeta(pq);
pushValue(pq, { name: "Ruski", age: 24 });
showMeta(pq);
