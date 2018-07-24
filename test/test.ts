import { expect } from "chai";
import { PriorityQueue } from "../";

interface Person {
    name: string;
    age: number;
}

describe("Native Values", function() {
    it("shall be empty initially", () => {
        const pq = new PriorityQueue<number>(n => n);
        expect(pq.size()).equals(0);
        expect(pq.empty()).is.true;
        expect(pq.top()).is.undefined;
    });

    it("shall push new values", () => {
        const pq = new PriorityQueue<number>(n => n);
        pq.push(10);
        expect(pq.size()).equals(1);
        expect(pq.empty()).is.false;
        expect(pq.top()).equals(10);

        pq.push(1);
        expect(pq.size()).equals(2);
        expect(pq.empty()).is.false;
        expect(pq.top()).equals(10);

        pq.push(100);
        expect(pq.size()).equals(3);
        expect(pq.empty()).is.false;
        expect(pq.top()).equals(100);
    });

    it("shall pop existing values", () => {
        const pq = new PriorityQueue<number>(n => n);
        pq.push(10);
        pq.push(1);
        pq.push(100);

        pq.pop();
        expect(pq.size()).equals(2);
        expect(pq.empty()).is.false;
        expect(pq.top()).equals(10);

        pq.pop();
        expect(pq.size()).equals(1);
        expect(pq.empty()).is.false;
        expect(pq.top()).equals(1);

        pq.pop();
        expect(pq.size()).equals(0);
        expect(pq.empty()).is.true;
        expect(pq.top()).is.undefined;
    });
});

describe("Objects", function() {
    it("shall be empty initially", () => {
        const pq = new PriorityQueue<Person>(p => p.age);
        expect(pq.size()).equals(0);
        expect(pq.empty()).is.true;
        expect(pq.top()).is.undefined;
    });

    it("shall push new values", () => {
        const pq = new PriorityQueue<Person>(p => p.age);
        pq.push({ name: "Alice", age: 10 });
        expect(pq.size()).equals(1);
        expect(pq.empty()).is.false;
        expect(pq.top()!.name).equals("Alice");

        pq.push({ name: "Bob", age: 1 });
        expect(pq.size()).equals(2);
        expect(pq.empty()).is.false;
        expect(pq.top()!.name).equals("Alice");

        pq.push({ name: "Charlie", age: 100 });
        expect(pq.size()).equals(3);
        expect(pq.empty()).is.false;
        expect(pq.top()!.name).equals("Charlie");
    });

    it("shall pop existing values", () => {
        const pq = new PriorityQueue<Person>(p => p.age);
        pq.push({ name: "Alice", age: 10 });
        pq.push({ name: "Bob", age: 1 });
        pq.push({ name: "Charlie", age: 100 });

        pq.pop();
        expect(pq.size()).equals(2);
        expect(pq.empty()).is.false;
        expect(pq.top()!.name).equals("Alice");

        pq.pop();
        expect(pq.size()).equals(1);
        expect(pq.empty()).is.false;
        expect(pq.top()!.name).equals("Bob");

        pq.pop();
        expect(pq.size()).equals(0);
        expect(pq.empty()).is.true;
        expect(pq.top()).is.undefined;
    });
});
