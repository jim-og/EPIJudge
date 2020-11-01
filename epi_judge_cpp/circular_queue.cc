#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
class Queue {
 public:
  Queue(size_t capacity)
    : entries_(capacity)
    , kScaleFactor(2)
    , head_(0)
    , tail_(0)
    , num_queue_elements_(0)
  {}

  void Enqueue(int x) {
    if (num_queue_elements_ == entries_.size())
    { // Need to resize
      // Rotate entries to appear consecutively
      std::rotate(entries_.begin(), entries_.begin() + head_, entries_.end());
      head_ = 0;
      tail_ = num_queue_elements_;
      entries_.resize(entries_.size() * kScaleFactor);
    }

    entries_[tail_] = x;
    tail_ = (tail_ + 1) % entries_.size();
    ++num_queue_elements_;
    return;
  }
  int Dequeue() {
    --num_queue_elements_;
    int result = entries_[head_];
    head_ = (head_ + 1) % entries_.size();
    return result;
  }
  int Size() const {
    return num_queue_elements_;
  }

protected:
  const int kScaleFactor;
  int head_;
  int tail_;
  int num_queue_elements_;
  std::vector<int> entries_;
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
