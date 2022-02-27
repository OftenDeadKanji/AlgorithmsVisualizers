package MVC.Sorter

abstract class Sorter {
    abstract fun sortAndReturnIndex(arrayToSort : Array<Int>, currentIndex : Int) : Int

    protected fun swap(array : Array<Int>, index1 : Int, index2 : Int)
    {
        val tmp = array[index1]
        array[index1] = array[index2]
        array[index2] = tmp
    }
}