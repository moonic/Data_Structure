public class Insertion
{
  public static void sort(Comparable[] a)
{ // 将a[]按升序排列
  int N = a.length;
  for (int i = 1; i < N; i++)
  { // 将 a[i] 插入到 a[i-1]、a[i-2]、a[i-3]...之中
    for (int j = i; j > 0 && less(a[j], a[j-1]); j--) 
  exch(a, j, j-1);
     }
  }
// less()、exch()、isSorted()和main()方法见“排序算法类模板”
}

//对于 0 到 N-1 之间的每一个 i ，将 a[i] 与 a[0] 到 a[i-1] 中比它小的所有元素依次有序地交换。
//在索引 i 由左向右变化的过程中，它左侧的元素总是有序的，所以当 i 到达数组的右端时排序就完成了。
