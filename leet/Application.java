package playground;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Application {

    
    public static void main(String[] args) {
        /*
        System.out.println(reverseString("hello"));
        System.out.println(canWinNim(4));
        System.out.println(getSum(-355,122));
        System.out.println(addDigits(393));
        int[] arr1 = new int[] {4,2,4,0,0,3,0,5,1,0};
        moveZeroes(arr1);
        System.out.println(Arrays.toString(arr1));
        int[] arr2 = new int[] {10};
        int[] arrRes = intersection(arr1,arr2);
        System.out.println(Arrays.toString(arrRes));
        ListNode tail = buildListNodes(new int[] {1,2,3,4,5,6});
        printListNodes(tail);
        deleteNode(tail.next.next);
        printListNodes(tail); 
        System.out.println(titleToNumber("BA"));
        System.out.println(isAnagram("anagram","nagara"));        
        
        int[] arr1 = new int[] {4,2,3};
        
        System.out.println(majorityElement(arr1));        
        System.out.println(containsDuplicate(arr1));
        System.out.println(Arrays.toString(intersect(arr1,arr2)));
        
        ListNode tail = buildListNodes(new int[] {});
        printListNodes(tail);
        tail = reverseList(tail);
        printListNodes(tail); 

        System.out.println(isPowerOfThree(4));
        System.out.println(isPowerOfThree(3));
        System.out.println(isPowerOfThree(27));
        
        
        System.out.println(isPowerOfTwo(9));
        System.out.println(isPowerOfTwo(8));
        System.out.println(isHappy(13));
        System.out.println(isHappy(14));
        System.out.println(isUgly(8));
        ListNode tail = buildListNodes(new int[] {1,1,1});
        printListNodes(tail);
        tail = deleteDuplicates(tail);
        printListNodes(tail);
        char[][] grid = new char[][] {
            "11000".toCharArray(),
            "11000".toCharArray(),
            "10100".toCharArray(),
            "10011".toCharArray(),
            "11110".toCharArray(),
            "00000".toCharArray(),
        };
        printIsland(grid); 
        */
        
        String testIpSequence = "25525511135";
        List<String> ipList = restoreIpAddresses(testIpSequence);
        for(String ip : ipList){
            System.out.println(ip);
        }
    }
    
    //https://leetcode.com/problemset/algorithms/ - 93
    public static List<String> restoreIpAddresses(String s) {
        IpChunk root = generateChunkTree(s);
        List<String> ipList = new ArrayList<String>();
        Deque<String> adressStack = new LinkedList<String>();
        return populateIpList(root, ipList, adressStack);
    }    
    
    private static HashMap<String, Boolean> ipChunkCandidates = new HashMap<String, Boolean>();
    
    private static class IpChunk {
        private int position;
        private int ipChunkInt;
        private String remSubSequence;
        private List<IpChunk> children;
        
        public IpChunk(int position, int IpChunkInt, String remSubSequence){
            this.position = position;
            this.ipChunkInt = IpChunkInt;
            this.remSubSequence = remSubSequence;
            this.children = new ArrayList<IpChunk>();
        }
        
        @Override
        public String toString(){
            return getSignature(this);
        }
    }

    private static List<String> populateIpList(IpChunk parent, List<String> ipList, Deque<String> adressStack){
        adressStack.push(Integer.toString(parent.ipChunkInt));
        if(parent.children != null){
            for(IpChunk child : parent.children){
                ipList.addAll(populateIpList(child, ipList, adressStack));
            }
            return new LinkedList<String>();
        }else{
            String validIp = "";
            for(String ipChunk : adressStack){
                validIp += ipChunk +  ".";
            }
            validIp = validIp.substring(0, validIp.length()-1);
            LinkedList<String> ipListSubset = new LinkedList<String>();
            ipListSubset.add(validIp);
            adressStack.pop();
            return ipListSubset;
        }
    }
    
    public static IpChunk generateChunkTree(String s){            
        IpChunk root = getNextValidChunk(new IpChunk(0,-1, s));
        if(root == null) return null;            
        _generateChunkTree(root);
        return root;
    }
        
    public static void _generateChunkTree(IpChunk parent){
        if(parent.position > 4 )return;
        
        //Check any possible child: a child can have between 1 and 3 digits
        IpChunk possibleChild = null;
        for(int endIdx = 1; endIdx < 4 && endIdx < parent.remSubSequence.length(); endIdx++){
            int nextNum = Integer.parseInt(parent.remSubSequence.substring(0, endIdx));
            String candidateSubequenceStr = parent.remSubSequence.substring(endIdx);
            possibleChild = new IpChunk(parent.position + 1,nextNum, candidateSubequenceStr);
            if(isValidIpChunk(possibleChild)){
                parent.children.add(possibleChild);
            }
        }
        
        //Recurse on the children
        for(IpChunk child : parent.children){
            _generateChunkTree(child);
        }
    }
    
    public static IpChunk getNextValidChunk(IpChunk candidateChunk){
        boolean isValid = false;
        for(int endIdx = 1; endIdx < 4 && endIdx < candidateChunk.remSubSequence.length(); endIdx++){
            int nextNum = Integer.parseInt(candidateChunk.remSubSequence.substring(0, endIdx));
            String candidateSubsequence = candidateChunk.remSubSequence.substring(endIdx);
            IpChunk candidate = new IpChunk(candidateChunk.position + 1,nextNum, candidateSubsequence );
            isValid |= isValidIpChunk(candidate);
            if(isValid){
                return candidate;
            }                
        }
        return null;
    }
    
    public static String getSignature(IpChunk candidateChunk){
        String signature = candidateChunk.position + ";" 
                            + candidateChunk.ipChunkInt + ";" 
                            + candidateChunk.remSubSequence;
        return signature;
    }
    
    
    public static boolean isValidIpChunk(IpChunk candidateChunk) {
        String signature = getSignature(candidateChunk);
        if(ipChunkCandidates.containsKey(signature))
            return ipChunkCandidates.get(signature);
        if(candidateChunk.ipChunkInt < 0 || candidateChunk.ipChunkInt > 255){
            ipChunkCandidates.put(signature, false);
            return false;
        }
        int remChunks = 4 - candidateChunk.position;
        //missing checks when reaching end of subsequence
        if(candidateChunk.remSubSequence.length() > 3*remChunks || 
                candidateChunk.remSubSequence.length() < remChunks){
            ipChunkCandidates.put(signature, false);
            return false;
        }
        if(candidateChunk.position > 4 
                || (candidateChunk.position == 4 
                        && candidateChunk.remSubSequence.length() > 0)){
            ipChunkCandidates.put(signature, false);
            return false;
        }
        boolean isValid = getNextValidChunk(candidateChunk) != null;
        ipChunkCandidates.put(signature, isValid);  
        return isValid;        
    }
    

    //https://leetcode.com/problemset/algorithms/ - 83
    public static ListNode deleteDuplicates(ListNode head) {
        ListNode node = head;
        while(node != null){
            if(node.next != null &&
                    node.val == node.next.val){
                node.next = node.next.next;
            }else{
                node = node.next;                
            }
        }
        return head;
    }

    
    public static boolean isUgly(int num){
        if(num < 1)return false;
        if(num == 1)return true;
            
        if( num % 2 == 0 ){
            return isUgly(num/2);
        }else if( num % 3 == 0){
            return isUgly(num/3);
        }else if( num % 5 == 0){
            return isUgly(num/5);            
        }else{
            return false;
        }
    }
    
    
    public static void printIsland (char[][] grid){

        int rowLength = grid.length;
        int colLength = -1;
        StringBuffer sb = new StringBuffer();
        for(int row = 0; row < rowLength; row++){
            colLength = grid[row].length;
            for(int col = 0; col < colLength; col++){
                sb.append(grid[row][col]);
            }
            sb.append("\n");
        }        
        System.out.println(sb);        
    }
    
    
    //https://leetcode.com/problemset/algorithms/ - 200
    //TODO: complete @ home
    public int numIslands(char[][] grid) {
        int islandId = 2;
        int islandCount = 0;
        int rowLength = grid.length;
        int colLength = -1;
        boolean topHit = false;
        boolean leftHit = false;
        boolean newIsland=false;
        
        for(int row = 0; row < rowLength; row++){
            colLength = grid[row].length;
            for(int col = 0; col < colLength; col++){
                //Earth !
                if(grid[row][col] == '1'){
                    //init test variables;
                    topHit = false;
                    leftHit = false;
                    newIsland = false;                    
                    
                    //Check if neighbors are already part of an island
                    //->top
                    if((row+1) < grid.length){
                    //->right  
                    }else if(false){
                      
                    //->bottom
                    }else if(false){
                    
                    //->left
                    }else if(false){
                        
                    }
                    
                    //decrement if coord. is a island junction point
                    if(topHit && leftHit){
                        islandCount--;
                    }
                    
                    //take on of the neighbor's id;
                }
            }
        }
        
        return islandId;
    }

    // you need to treat n as an unsigned value
    //https://leetcode.com/problemset/algorithms/ - 191
    public static int hammingWeight(int n) {
        int count = 0;
        for (int i = 0; i < 32; i++){
            if((n & 0x1) == 0x1)
                count++;
            n = n >>1;
        }
        return count;
    }
    
    //https://leetcode.com/problemset/algorithms/ - 202
    private static HashSet<Integer> mySet = new HashSet<Integer>();
    public static boolean isHappy(int n) {
      //check if happy
        int sum = 0;
        int dec = 0;
        while(n > 0){
            dec = n % 10;
            sum += dec*dec;
            n /= 10;
        }
        if(sum == 1){
            return true;
        }else{
            //cycle detection
            if(mySet.contains(sum)){
                return false;
            }else{
                mySet.add(sum);
                return isHappy(sum);
            }
        }
    }
    
    // 000100
    // 110001
    //https://leetcode.com/problemset/algorithms/ - 231
    public static boolean isPowerOfTwo(int n) {
        if(n < 1)return false;        
        return (n & (n -1)) == 0;
    }

    //https://leetcode.com/problemset/algorithms/ - 326
    //https://leetcode.com/articles/power-of-three/#approach-2-base-conversion-accepted
    public static boolean isPowerOfThree(int n) {
        
        //naive division C:O(N)
        if (n < 0)return false;
        double nDouble = n;
        while(n>1){
            nDouble /= 3.0;
            n = (int) nDouble;
            if((nDouble - ((double)n)) != 0){
                return false;
            }
        }
        return true;
        /*
        //naive Use math libraries...
        if(n < 0) return false;
        double expDouble = Math.log10(n)/-((double)expInt))Math.log10(3);
        int expInt = (int) expDouble;
        
        return (expDouble-((double)expInt)) == 0;*/
    }
    
    
    //https://leetcode.com/problemset/algorithms/ - 206
    public static ListNode reverseList(ListNode head) {
        if (head == null)return null;
        
        //crazy swap: C:O(N), M:O(N)
        ListNode current = head;
        ListNode previous = null;
        ListNode temp = null;
        while(current != null){
            temp = current.next;
            current.next = previous;
            previous = current;
            current = temp;
        }
        return previous; 
        
        //Naive stack approach: C:O(N), M:O(N)
        /*
        //push to a stack
        LinkedList<ListNode> stack = new LinkedList<ListNode>();
        ListNode node = head;
        while(node != null){
            stack.push(node);
            node = node.next;
        }

        //pop stack and enqueue
        head = stack.pop();
        node = head;
        while(!stack.isEmpty()){
            node.next = stack.pop();
            node = node.next;
        }
        node.next = null;
        
        return head;*/
        
    }


    //https://leetcode.com/problemset/algorithms/ - 350
    public static int[] intersect(int[] nums1, int[] nums2) {
        if(nums1 == null || nums2 == null 
                || nums1.length==0 || nums2.length == 0)
                    return new int[] {};
        
        
        int[] smallArr;
        int[] bigArr;   

        if(nums1.length < nums2.length){
            bigArr = nums2;
            smallArr = nums1;
        }else{
            bigArr = nums1;
            smallArr = nums2;
        }
        
        Arrays.sort(nums1);
        Arrays.sort(nums2);
        
        ArrayList<Integer> outputList = 
                new ArrayList<Integer>(smallArr.length);
        
        int j=0;        
        for(int i = 0; i < smallArr.length; i++){
            if(smallArr[i] > bigArr[j]){
                while(j < bigArr.length 
                        && smallArr[i] > bigArr[j]){
                    j++;
                }
            }
            
            if(j >= bigArr.length ){
                break;
            }
            if(smallArr[i] == bigArr[j]){
                outputList.add(smallArr[i]);
                j++;
            }
            if(j >= bigArr.length ){
                break;
            }
        }
        
        int[] outputArr = new int [outputList.size()];
        int i = 0;
        for(int num : outputList){
            outputArr[i++] = num;
        }
        return outputArr;
        //naive linear lookup : M:O(1), C:O(N^2)
        
        //sort and then merge : M:O(1), C:O(n*log(n))
        
        //if both arrays sorted : merge variant M:O(1), C:O(N)
        //if nums1>>nums2 pick nums1 and check all nums2 elements
        //M:O(1), C:O(N*M)
        //Sort nums1 for each num2 check nums1 M:O(1), C:O(N*log(N) + N*M)
    }
    

    //https://leetcode.com/problemset/algorithms/ - 217
    public static boolean containsDuplicate(int[] nums) {
        if(nums == null || nums.length < 2)return false;
        
        //bubble sort variant
        //C:O(N^2), M:O(1)
        /*
        boolean swapped=true;
        int val = 0;
        while(swapped){
            swapped = false;
            for(int i = 0; i < nums.length-1; i++){
                if(nums[i] == nums[i+1]){
                    return true;
                }else if (nums[i] >= nums[i+1]){
                    val = nums[i+1];
                    nums[i+1] = nums[i];
                    nums[i] = val;
                    swapped = true;
                }
            }
        }
        return false;*/
        
        //hashset C:O(N), M:O(N)
        HashSet<Integer> numsHash = new HashSet<Integer>();
        for(int num : nums){
            if(numsHash.contains(num)){
                return true;
            }else{
                numsHash.add(num);
            }
        }
        return false;
    }
    //3,4,3,5   ,3,3,4,0
    //TODO: a mathematical solution must exist
    //https://leetcode.com/problemset/algorithms/ - 169
    public static int majorityElement(int[] nums) {
        HashMap<Integer,Integer> hitCnt = new HashMap<Integer,Integer>();
        Integer value = null;
        for(int num : nums){
            value = hitCnt.get(num);
            if(value != null){
                hitCnt.put(num, value + 1);
            }else{
                hitCnt.put(num,1);
            }
        }
        Integer maxKey = null;
        Integer maxValue = 0;
        for(Integer key : hitCnt.keySet()){
            if(hitCnt.get(key) > maxValue){
                maxKey = key;
                maxValue = hitCnt.get(key);
            }
        }
        return maxKey;
    }

    //https://leetcode.com/problemset/algorithms/ - 242
    public static boolean isAnagram(String s, String t) {
        if(s == null || t == null || s.length() != t.length()){
            return false;
        }
        //could use a hashmap instead
        int [] hitCnt = new int[26];
        char[] charArrS = s.toCharArray();
        char[] charArrT = t.toCharArray();
        for(int i = 0; i < s.length(); i++){
            hitCnt[((byte)charArrS[i]) - ((byte)'a')]++;
            hitCnt[((byte)charArrT[i]) - ((byte)'a')]--;
        }
        for(int cnt : hitCnt){
            if(cnt != 0)return false;
        }
        return true;
        
    }

    
    //https://leetcode.com/problemset/algorithms/ - 171
    public static int titleToNumber(String s) {
        if(s == null)return 0;
        
        char[] charArr = s.toCharArray();
        int colNum = 0;
        for(int i=0; i < charArr.length ; i++){
            int a = (((byte) charArr[i]) - ((byte) 'A') + 1);
            colNum += ((int)Math.pow(26, charArr.length - i  -1))*a;
        }
        return colNum;
    }

    //https://leetcode.com/problemset/algorithms/ - 100
    public static boolean isSameTree(TreeNode p, TreeNode q) {
        if(p == null && q != null){
            return false;
        }else if(p != null && q == null){
            return false;
        }else if(p == null && q == null){
            return true;
        }else {
            return p.val == q.val &&
                    isSameTree(p.left, q.left) 
                    && isSameTree(p.right,q.right);
        }        
    }
    
    //https://leetcode.com/problemset/algorithms/ - 237
    public static void deleteNode(ListNode node) {
        if(node == null)return;
        
        while(node.next != null){
            node.val = node.next.val;
            if(node.next.next == null){
                node.next = null;
                break;
            }
            node = node.next;
        }
    }
    
    public static ListNode buildListNodes(int[] array){
        if(array == null || array.length == 0) return null;
        
        ListNode tail = new ListNode(0);
        ListNode node = tail;
        for(int val : array){
            node.next = new ListNode(val);
            node = node.next;            
        }
        return tail.next;
    }
    
    
    public static void printListNodes(ListNode list){
        if(list == null)return;
        StringBuffer sb = new StringBuffer();
        while(list != null){
            sb.append(list.val);
            sb.append(",");
            list = list.next;
        }        
        System.out.println(sb.toString());
    }


    //https://leetcode.com/problemset/algorithms/ - 349
    public static int[] intersection(int[] nums1, int[] nums2) {
        
        
        //TRIVIAL SOLUTION -> memory = O(N), speed O(N)
        if(nums1 == null || nums2 == null 
                || nums1.length == 0 || nums2.length == 0)
                return new int[] {};

        //Set of one array
        HashSet<Integer> S1 = new HashSet<Integer>(nums1.length);        
        for(int num : nums1){
            S1.add(num);
        }
        
        
        //intersect arrays as Sets
        int minLen = Math.min(nums1.length, nums2.length);
        HashSet<Integer> intersect = new HashSet<Integer>(minLen);
        
        for(int num : nums2){
            if(S1.contains(num)){
                intersect.add(num);        
            }
        }
        
        //build back intersection set as array
        int[] arrInt = new int[intersect.size()];
        int i = 0;
        for(int num : intersect){
            arrInt[i++] = num;
        }
        return arrInt;       
        
    }
    
    //https://leetcode.com/problemset/algorithms/ - 283
    public static void moveZeroes(int[] nums) {        
        if (nums == null || nums.length <= 1) return;
        
        int numZ = 0;
        int nextCandidateIdx = 1;
        for(int i=0; i < nums.length-1 && nextCandidateIdx < nums.length; i++){
            if(nums[i] != 0){
                nextCandidateIdx = i+1;
                continue;                
            }
            
            //find next candidate and count zeroes
            while(nextCandidateIdx < nums.length &&
                        nums[nextCandidateIdx] == 0 ){
                nextCandidateIdx++;
            }
            
            //swap the candidate to its replacing position
            if(nextCandidateIdx < nums.length){                
                nums[i] = nums[nextCandidateIdx];
                nums[nextCandidateIdx] = 0;         
            }
            
            //move to next potential candidate
            nextCandidateIdx++;            
        }
        //variant of bubble sort pushing all zeroes at the end 
        /*
        boolean swapped = true;
        int tmp = -1;
        while(swapped){
            swapped = false;
            for(int i = 0; i < nums.length-1; i++ ){
                if(nums[i] == 0 && nums[i+1] != 0){
                    tmp = nums[i+1];
                    nums[i + 1] = nums[i];
                    nums[i] = tmp;
                    swapped = true;
                }
            }
        }*/
    }

    //https://leetcode.com/problemset/algorithms/ - 226
    public TreeNode invertTree(TreeNode root) {
        if (root == null)return null;
        
        if(root.right != null){
            invertTree(root.right);
        }
        
        if(root.left != null){
            invertTree(root.left);
        }
        
        TreeNode tmp = root.right;
        root.right = root.left;
        root.left = tmp;
        
        return root;
    }
    
    public static int maxDepth(TreeNode root) {
        if(root == null)return 0;
        int leftDepth = 1;
        if(root.left != null){
            leftDepth =  1 + maxDepth(root.left);
        }
        
        int rightDepth = 1;
        if(root.right != null){
            rightDepth =  1 + maxDepth(root.right);
        }
        
        if(leftDepth > rightDepth){
            return leftDepth;
        } else{
            return rightDepth;
        }
    }
    
    
    //https://leetcode.com/problemset/algorithms/ - 258
    public static int addDigits(int num) {
        if(num == 0)return 0;
        if(num % 9 == 0)return 9;
        return num - ((num / 9) * 9);
        /*
        if (num <= 9 ){
            return num;
        }else{
            int val = 0;
            while(num > 0){
                val += num % 10;
                num /= 10;
            }
            return addDigits(val);
        }
        */
    }

    //https://leetcode.com/problemset/algorithms/ - 344
    public static String reverseString(String s) {
        if(s == null || s.length() <= 1)return s;
        char[] strArr = new char [s.length()];
        for(int i = 0; i < s.length(); i++){
            strArr[s.length()-1 -i] = s.charAt(i);
        }
        return new String(strArr);
    }
    
    //https://leetcode.com/problemset/algorithms/ - 292
    public static boolean canWinNim(int n) {        
       return (n % 4) != 0;
    }

    //https://leetcode.com/problemset/algorithms/ - 371
    public static int getSum(int a, int b) {
        int offset = 0x1;
        int carry = 0x0;
        int sum = 0x0;
        int a_i =0;
        int b_i =0;
        for(int i = 0; i < 32; i++){
            a_i = a & offset;
            b_i = b & offset;
            sum |= (a_i ^ b_i) ^ carry;
            carry = (a_i & b_i) | (a_i & carry) | (b_i & carry);
            carry <<=1;
            offset <<= 1;            
        }        
        return sum;
    }
    
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }        
    }
}
