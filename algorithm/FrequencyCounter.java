public class FrequencyCounter
  {
    public static void main(String[] args)
      {
        int minlen = Integer.parseInt(args[0]); // 最小键长
        ST<String, Integer> st = new ST<String, Integer>();
      while (!StdIn.isEmpty())
      { // 构造符号表并统计频率
    String word = StdIn.readString();
      if (word.length() < minlen) continue; // 忽略较短的单词
      if (!st.contains(word)) st.put(word, 1);
     else st.put(word, st.get(word) + 1);
  }
// 找出出现频率最高的单词
String max = " ";
% more tinyTale.txt
it was the best of times it was the worst of times
it was the age of wisdom it was the age of foolishness
it was the epoch of belief it was the epoch of incredulity
it was the season of light it was the season of darkness
it was the spring of hope it was the winter of despair
小型测试输入
371

     st.put(max, 0);
    for (String word : st.keys())
      if (st.get(word) > st.get(max))
      max = word;
    StdOut.println(max + " " + st.get(max));
      }
  }
