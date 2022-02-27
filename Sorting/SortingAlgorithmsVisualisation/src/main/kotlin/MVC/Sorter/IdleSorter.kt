package MVC.Sorter

class IdleSorter : Sorter(){
    override fun sortAndReturnIndex(arrayToSort: Array<Int>, currentIndex: Int): Int {
        return currentIndex
    }
}