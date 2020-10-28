package diffprocessor;

/**
 * Created by VavilauA on 6/19/2015.
 */
public class Processor {
    private static Double eps = 1e-7;

    public Processor(long limit) {
        // TODO: initialize.
    }

    private int compare(Double a, Double b) {
        if (Math.abs(a - b) <= eps)
            return 0;
        if (a > b)
            return 1;
        else
            return -1;
    }

    public void doProcess(SortedLimitedList<Double> mustBeEqualTo, SortedLimitedList<Double> expectedOutput) {
        // TODO: make "mustBeEqualTo" list equal to "expectedOutput".
        // 0. Processor will be created once and then will be used billion times.
        // 1. Use methods: AddFirst, AddLast, AddBefore, AddAfter, Remove to modify list.
        // 2. Do not change expectedOutput list.
        // 3. At any time number of elements in list could not exceed the "Limit".
        // 4. "Limit" will be passed into Processor's constructor. All "mustBeEqualTo" and "expectedOutput" lists will have the same "Limit" value.
        // 5. At any time list elements must be in non-descending order.
        // 6. Implementation must perform minimal possible number of actions (AddFirst, AddLast, AddBefore, AddAfter, Remove).
        // 7. Implementation must be fast and do not allocate excess memory.
        SortedLimitedList.Entry<Double> iterMust = mustBeEqualTo.first;
        SortedLimitedList.Entry<Double> iterExp = expectedOutput.first;
        while (iterMust != null) {
            if (iterExp == null) {
                SortedLimitedList.Entry<Double> tmp = iterMust.getNext();
                mustBeEqualTo.remove(iterMust);
                iterMust = tmp;
                continue;
            }

            int comp = compare(iterMust.getValue(), iterExp.getValue());
            switch (comp) {
                case 0:
                    iterMust = iterMust.getNext();
                    iterExp = iterExp.getNext();
                    break;
                case -1:
                    SortedLimitedList.Entry<Double> tmp = iterMust.getNext();
                    mustBeEqualTo.remove(iterMust);
                    iterMust = tmp;
                    break;
                case 1:
                    iterExp = iterExp.getNext();
                    break;
            }
        }

        iterMust = mustBeEqualTo.first;
        iterExp = expectedOutput.first;
        while (iterExp != null) {
            if (iterMust == null)
            {
                mustBeEqualTo.addLast(iterExp.getValue());
                iterExp = iterExp.getNext();
                continue;
            }
            int comp = compare(iterMust.getValue(), iterExp.getValue());
            switch (comp) {
                case 0:
                    iterMust = iterMust.getNext();
                    iterExp = iterExp.getNext();
                    break;
                case -1:
                    mustBeEqualTo.addAfter(iterMust, iterExp.getValue());
                    iterExp = iterExp.getNext();
                    iterMust = iterMust.getNext();
                    break;
                case 1:
                    mustBeEqualTo.addBefore(iterMust, iterExp.getValue());
                    iterExp = iterExp.getNext();
                    break;
            }
        }
    }
}
