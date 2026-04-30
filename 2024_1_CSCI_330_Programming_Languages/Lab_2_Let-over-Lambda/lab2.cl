;/**
; * @file lab2.cl
; * @author Patrick McGrath, CSCI 330, VIU
; * @version 1.0
; * @date February, 2024
; * 
; *  Lab 2: Let-over-Lambda
; *  Copyright (C) 2024 Patrick McGrath
; *
; *  This program is free software: you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation, either version 3 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License
; *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
; */

; valid strings for letter grades
(defconstant VALIDLETGRADES
   '("A+" "A" "A-" "B+" "B" "B-" "C+" "C" "C-" "D" "F" "INC" "CR" "TRF" "WDR" "UW" "CS" "NP"))



(defun buildGrade (G isR)
    (let (
            ;local variables
            ;all are set to nil to make them invalid.
            ;except for: 
            ;   isRq is set to 0 because nil is a valid value,
            ;   GPA and WGPA are set to 0.0 as default and to make them floats and not ints
            ;   and backupG is a backup pointer to G
            ;assigned denotes whether the variables have been set using setALL.
            (backupG G)
            (assigned nil)
            (Area nil)
            (Cnum nil)
            (Cred nil)
            (LetG nil)
            (isrq 0)
            (GPA 0.0)
        )
        (labels (
            ;local functions
                ; getArea, getCnum, getCred, getGPA and getLetG functions for returning stored values.
                ; if no value has been assigned, nil is returned, otherwise the stored values are returned
                (getArea () 
                    (cond
                        ((equalp assigned nil) nil)
                        (t Area)
                    )
                )
                (getCnum ()
                    (cond
                        ((equalp assigned nil) nil)
                        (t Cnum)
                    )
                )
                (getCred () 
                    (cond
                        ((equalp assigned nil) nil)
                        (t Cred)
                    )
                )
                (getGPA ()
                    (cond
                        ((equalp assigned nil) nil)
                        (t GPA)
                    )
                )
                (getLetG () 
                    (cond
                        ((equalp assigned nil) nil)
                        (t LetG)
                    )
                )

                ; getWGPA function,
                ; similar to the previous funcitons, but instead of returning a stored value, returned a calculated one
                (getWGPA () 
                    (cond
                        ((equalp assigned nil) nil)
                        (t (* GPA Cred))
                    )
                )

                ; isReq function,
                ; similar to previous functions, but if local variables have not been assigned, nil cannot be returned.
                ; but, since the local variable starts as 0, it can be returned regardless if assigned is nil or t
                (isReq () isrq)

                ; isValid function for checking if stored / passed grade is valid. 
                ; takes 1 parameter, a single 4-component Grade
                ; if no parameter was passed during call, arg1 will be optionally assigned nil
                ; isValid will check if arg1 is nil, 
                ;   validGrade is called on either the original Grade used for dispatcher if setALL has not been called yet
                ;   if setALL was used, a list of the local variables is used for validGrade
                ; if arg1 was a passed parameter, validGrade is called on it instead
                (isValid (arg1)
                    (cond
                        ((equalp arg1 nil) (validGrade (if (equalp assigned t) (list Area Cnum Cred LetG) backupG)))
                        (t (validGrade arg1))
                    )
                )

                ; getAsList function,
                ; returns a list of local variables in the expectect Grade format
                ; will first check if variables have been assigned.
                ; if they have not been assigned, instead nil is returned
                (getAsList () 
                    (cond
                        ((equalp assigned t) (list Area Cnum Cred LetG))
                        (t nil)
                    )
                )


                ; meetsReq function,
                ; will check 2 grades against each other depending on whether the locally stored grade's isrq is nil or t.
                ; if isrq is t, then the passed grade is checked against the stored one for meeting requirements using meetsReqold
                ; if isrq is nil, then the stored grade is checked against the passed one.
                ; if the check passes, t is returned, otherwise nil.
                ; if either the stored grade has not been assigned or the passed grade is not valid, nil is returned.
                (meetsReq (arg1)
                    (cond
                        ((equalp assigned nil) nil)
                        ((equalp (validGrade arg1) nil) nil)
                        ((equalp isrq t) (meetsReqOLD (getAsList) arg1))
                        ((equalp isrq nil) (meetsReqOLD arg1 (getAsList)))
                        (t nil)
                    )
                )

                ; setAll function for assigning local variables' values
                ; takes 2 parameters, a signle 4-component Grade and a boolean
                ; checks if Grade is valid by calling validGrade (not isValid, as not passing a parameter will cause it default to the original used to created dispatcher), 
                ; if it is, each item is (calculated and) copied to its local variable
                ; then the 2nd parameter is copied to is local variable, after it has been converted into strictly nil/t
                ; finally, the assigned variable is updated to say that setAll was successfull. 
                ; if dispatcher is called using invalid orginal grades, assigned will remain nil
                (setAll (arg1 arg2)
                    (when (ValidGrade arg1)
                        (setf Area (car arg1))
                        (setf Cnum (car (cdr arg1)))
                        (setf Cred (car (cdr (cdr arg1))))
                        (setf LetG (car (cdr (cdr (cdr arg1)))))
                        (setf GPA (lettertoGPA (car (cdr (cdr (cdr arg1))))))
                        (setf isrq (anytoT arg2))
                        (setf assigned t)
                    )
                )
        )

            ; Attempt to assign local variables using passed parameters
            ; if invalid G is passed, assigned will remain nil and nothing else will be updated. 
            (setAll G isR)
            (lambda (cmd &optional (arg1 nil) (arg2 nil))
                ; build and return dispatcher as lambda function
                ; run whichever local function corresponds to the caller's commands
                (cond
                    ((equalp cmd 'getArea) (getArea))
                    ((equalp cmd 'getCnum) (getCnum))
                    ((equalp cmd 'getCred) (getCred))
                    ((equalp cmd 'getGPA) (getGPA))
                    ((equalp cmd 'getLetG) (getLetG))
                    ((equalp cmd 'getWGPA) (getWGPA))
                    ((equalp cmd 'isReq) (isReq))
                    ((equalp cmd 'isValid) (isValid arg1))
                    ((equalp cmd 'getAsList) (getAsList))
                    ((equalp cmd 'meetsReq) (meetsReq arg1))
                    ((equalp cmd 'setAll) (setAll arg1 arg2))
                    (t (format t "Error: not a valid command ~A~%" cmd))
                )
            )
        )
    )
)

; Helper function for converting anything that is not nil into t
(defun anytoT (x)
    (cond
        ((equalp x nil) nil)
        (t t)
    )
)


; gpaCalc function,
; takes a list of Grade dispatchers as a parameter.
; calculates the weighted gpa of all the valid grades in the list.
; if passed parameter is not a list, error is printed.
; if it is a list, this function assumes all elements of the list are dispatchers of Grades.
; If there are no valid grades, 0 is returned.
; helper functions gpaCalchead and gpaCalchelp are used
(defun gpaCalc (Grades)
    (cond
        ((not (listp Grades)) (format t "Error, not a list: ~A~%" Grades))
        (t (gpaCalchead (list 0.0 0 Grades)))
    )
)


; head healper for gpaCalc
; takes a list (L = '(wgpa credits Grades-dispatchers)
; returns the calculated weighted gpa of all valid grades in list
; no error checking is done on L as it is a helper function
; base case is when Grades-dispatchers is null, then the wgpa is returned.
; else, this function is recursively called on the return of the the secondary helper,
; which is used to process the first element of the grades-dispatcher.
; each time the grades-dispatcher portion gets closer to nil, triggering base case here.
(defun gpaCalchead (L)
    (cond
        ((null (car (cdr (cdr L)))) (car L))
        (t (gpaCalchead (gpaCalchelp L)))
    )
)

; gpaCalchelp secondary helper function.
; Parameter and return are same form, L = '(gpa credits Grades-dispatchers).
; should only be called from gpaCalchead, so no checks are done.
; If Grades is null, L is returned. (shouldn't happen)
; but because of this, this function can be called recursively indefinitely without error or incorrect result. 
; if the first dispatcher's stored gpa is nil, that grade is skipped
; if the first dispatcher's 'isValid call returns nil, that grade is skipped
; if the first dispatcher's credits is 0, that grade is skipped, this is to avoid dividing by 0.
; else, a new L is returned
; the new L is 
;   wgpa = ((wgpa * credits) + ((1st wgpa)/(credits + (1st credit))
;   credits = credits + (1st credit)
;   Grades-disp = (cdr Grades-disp)
(defun gpaCalchelp (L)
    (cond
        ((null (car (cdr (cdr L)))) L)
        ; (car (car (cdr (cdr L)))) = The first grade dispatcher
        ; (car L) = wgpa
        ; (car (cdr L)) = credits
        ; (cdr (car (cdr (cdr L)))) = the remaining dispatchers
        ((equalp (funcall (car (car (cdr (cdr L)))) 'getLetG) nil) (list (car L) (car (cdr L)) (cdr (car (cdr (cdr L))))))
        ((equalp (funcall (car (car (cdr (cdr L)))) 'isValid) nil) (list (car L) (car (cdr L)) (cdr (car (cdr (cdr L))))))
        ((equalp (funcall (car (car (cdr (cdr L)))) 'getCred) 0) (list (car L) (car (cdr L)) (cdr (car (cdr (cdr L))))))
        (t (list (/ 
                    (+ (* (car L) (car (cdr L)))
                        (funcall (car (car (cdr (cdr L)))) 'getWGPA)
                    )
                    (+ (car (cdr L)) (funcall (car (car (cdr (cdr L)))) 'getCred))
                )
                (+ (car (cdr L)) (funcall (car (car (cdr (cdr L)))) 'getCred))
                (cdr (car (cdr (cdr L))))
            )
        )
    )
)






; meetsAllreqs function.
; takes two list of grade-dispatcher, the first the requried list and the second the actual list.
; will return t if all valid grades in Rlist have at least one met grade in Alist using helper functions
; else each unmet required grade is printed and nil returned. 
; if either Alist or Rlist are not lists, error is printed and nil returned.
; if there are no valid required grades, t is returned
(defun meetsAllreqs (Rlist Alist)
   (cond
      ((not (listp Rlist)) (format t "Error, Requirements list not a list: ~A~%" Rlist))
      ((not (listp Alist)) (format t "Error, Course list not a list: ~A~%" Alist))
      ((equalp (length Rlist) 0) t)
      (t (if (equalp (meetsallhelp-one Rlist Alist) 0) nil t))
   )
)

; head helper function for meetsAllreqs.
; takes the 2 lists from meetsAllreqs
; if Alist meets Rlist, 1 is returned, else 0.
; 1 and 0 is used so that all elements are checked in a logical "and" manner, using *.
; otherwise, using t and nil with "and" will break on the first nil.
; nzto is used to convert nil to 0 and t to 1.
; if the Rlist is empty, 1 is returned.
; else this function returns the product of:
;       the return of the first element of Rlist checked against all of Alist using the secondary helper function.
;   and the return of this function recursively called on the remainder of Rlist and all of Alist.
(defun meetsallhelp-one (Rlist Alist)
   (cond
      ((null Rlist) 1)
      (t (* (nzto (meetsallhelp-two (car Rlist) Alist)) (nzto (meetsallhelp-one (cdr Rlist) Alist))))
   )
)


; secondary helper function
; takes a single gradedispatcher of a required grade and a list of grade dispatchers to check it against.
; if R is not valid, it is not required and t is returned.
; if Alist is empty, then R was not met. it is printed and nil is returned.
; else 
;       if either the first element of Alist meets R or any other element does, t is returned
;       else nil
; R is checked against the first element of Alist by using R's 'meetsReq function and Alist's 1st element's 'getAsList function.
; The remainder of the list is checked by recursive call on this function using the remainder of Alist.
; this function can use nil and t, because logical "or" requires checking all parameters.
(defun meetsallhelp-two (R Alist)
   (cond
      ((not (funcall R 'isValid)) t)
      ((null Alist) (format t "~A~%" (funcall R 'getAsList)))
      (t (or (funcall R 'meetsReq (funcall (car Alist) 'getAsList)) (meetsallhelp-two R (cdr Alist))))
   )
)


; basic helper for converting 
; nil to zero and t to one
(defun nzto (x)
    (cond
        ((equalp x nil) 0)
        ((equalp x t) 1)
        (t x)
    )
)
















;LAB 1 CONTENT

;  validGrade takes a grade in the form of list.
;  function simply tests the list and each of its elements to see if they are valid.
;  if any test fails, an error is printed and nil is returned.
;  otherwise, t is returned.
;  a valid grade is a list of 4 elements
;  element 1 is a string found in the list VALIDAREAS
;  element 2 is an integer, where 100 <= element =< 499
;  element 3 is an integer, where 0 <= element =< 5
;  element 4 is a string found in the list VALIDLETGRADES
(defun validGrade (G)
   (cond
      ((not (listp G)) (format t "Error, not a list: ~A~%" G))
      ((not (equalp (length G) 4)) (format t "Error, list does not have 4 items: ~A~%" G))
      ((not (stringp (car G))) (format t "Error, not a string: ~A~%" (car G)))
      ((not (integerp (car (cdr G)))) (format t "Error, not an integer: ~A~%" (car (cdr G))))
      ((not (integerp (car (cdr (cdr G))))) (format t "Error, not an integer: ~A~%" (car (cdr (cdr G)))))
      ((not (stringp (car (cdr (cdr (cdr G)))))) (format t "Error, not a string: ~A~%" (car (cdr (cdr (cdr G))))))
      ((not (searchlist VALIDAREAS (car G))) (format t "Error, not a valid department: ~A~%" (car G)))
      ((< (car (cdr G)) 100) (format t "Error, Course number less than 100: ~A~%" (car (cdr G))))
      ((> (car (cdr G)) 499) (format t "Error, Course number more than 499: ~A~%" (car (cdr G))))
      ((< (car (cdr (cdr G))) 0) (format t "Error, Course weight less than 0: ~A~%" (car (cdr (cdr G)))))
      ((> (car (cdr (cdr G))) 5) (format t "Error, Course weight more than 5: ~A~%" (car (cdr (cdr G)))))
      ((not (searchlist VALIDLETGRADES (car (cdr (cdr (cdr G)))))) (format t "Error, not a valid grade: ~A~%" (car (cdr (cdr (cdr G))))))
      (t t)
   )
)

; this function is a duplicate of validGrade, 
; except there are no print statements. 
; This is to avoid printing errors twice during gpa calculation 
(defun validGradenoprint (G)
   (cond
      ((not (listp G)) nil)
      ((not (equalp (length G) 4)) nil)
      ((not (stringp (car G))) nil)
      ((not (integerp (car (cdr G)))) nil)
      ((not (integerp (car (cdr (cdr G))))) nil)
      ((not (stringp (car (cdr (cdr (cdr G)))))) nil)
      ((not (searchlist VALIDAREAS (car G))) nil)
      ((< (car (cdr G)) 100) nil)
      ((> (car (cdr G)) 499) nil)
      ((< (car (cdr (cdr G))) 0) nil)
      ((> (car (cdr (cdr G))) 5) nil)
      ((not (searchlist VALIDLETGRADES (car (cdr (cdr (cdr G)))))) nil)
      (t t)
   )
)




; recursive helper function for seeing if item (val) is in list (L)
; returns t if it is in list
; if its not, returns nil
(defun searchlist (L val)
   (cond
      ((null L) nil)
      ((equalp val (car L)) t)
      (t (searchlist (cdr L) val))
   )
)












; letterToGPA function takes a letter grade in the form of a string
; initial test is done to see if parameter passed was a string, printing error if it fails
; function then compares string to "AUD" and if same, returns true.
; this is done first because AUD is not in VALIDLETGRADES, but AUD is acceptable
; next, function searches VALIDLETGRADES for string. if not found, nil returned and error printed
; string must be in VALIDLETGRADES, so its corresponding numerical value is returned, or nil, whichever is appropriate
; return values:
;  A+ 4.33    B+ 3.33    C+ 2.33    D  1.00
;  A  4.00    B  3.00    C  2.00    F  0.00
;  A- 3.67    B- 2.67    C- 1.67    UW 0.00
;  INC nil    WDR nil    NP nil     CS nil
;  CR nil     TRF nil    AUD nil
(defun letterToGPA (letterGrade)
   (cond
      ((not (stringp letterGrade)) (format t "Error: not a string.~%"))
      ((equalp letterGrade "AUD") nil)
      ((not (searchlist VALIDLETGRADES letterGrade)) (format t "Error, not a valid grade: ~A~%" letterGrade))
      ((equalp letterGrade "A+") 4.33)
      ((equalp letterGrade "A") 4.00)
      ((equalp letterGrade "A-") 3.67)
      ((equalp letterGrade "B+") 3.33)
      ((equalp letterGrade "B") 3.00)
      ((equalp letterGrade "B-") 2.67)
      ((equalp letterGrade "C+") 2.33)
      ((equalp letterGrade "C") 2.00)
      ((equalp letterGrade "C-") 1.67)
      ((equalp letterGrade "D") 1.00)
      ((equalp letterGrade "F") 0.00)
      ((equalp letterGrade "UW") 0.00)
      ((equalp letterGrade "INC") nil)
      ((equalp letterGrade "WDR") nil)
      ((equalp letterGrade "NP") nil)
      ((equalp letterGrade "CS") nil)
      ((equalp letterGrade "CR") nil)
      ((equalp letterGrade "TRF") nil)
      (t (format t "Error: Something unexpected happened.~%"))
   )
)



; this function is a duplicate of letterToGPA
; except there are no print statements. 
; This is to avoid printing errors twice during gpa calculation 
(defun letterToGPAnoprint (letterGrade)
   (cond
      ((not (stringp letterGrade)) nil)
      ((equalp letterGrade "AUD") nil)
      ((not (searchlist VALIDLETGRADES letterGrade)) nil)
      ((equalp letterGrade "A+") 4.33)
      ((equalp letterGrade "A") 4.00)
      ((equalp letterGrade "A-") 3.67)
      ((equalp letterGrade "B+") 3.33)
      ((equalp letterGrade "B") 3.00)
      ((equalp letterGrade "B-") 2.67)
      ((equalp letterGrade "C+") 2.33)
      ((equalp letterGrade "C") 2.00)
      ((equalp letterGrade "C-") 1.67)
      ((equalp letterGrade "D") 1.00)
      ((equalp letterGrade "F") 0.00)
      ((equalp letterGrade "UW") 0.00)
      ((equalp letterGrade "INC") nil)
      ((equalp letterGrade "WDR") nil)
      ((equalp letterGrade "NP") nil)
      ((equalp letterGrade "CS") nil)
      ((equalp letterGrade "CR") nil)
      ((equalp letterGrade "TRF") nil)
      (t nil)
   )
)







; helper function
; just converts nil to 0.
; if x is not nil, then x is returned, regardless of type
(defun niltozero (x)
   (cond
      ((equalp x nil) 0)
      (t x)
   )
)





; meetsReq function, takes required grade and actual grade as two lists
; function tests if the two lists are valid grades and if the 2nd meets or exceeds the requirements of the 1st
; to meet or exceed requirements, they must both be valid, the first 3 elements must be identical and
; the final elements numerical values must be (Act >= Req) or (Act = "TRF")
; first tests both with valisGrade and if either fails, returns nil
; then checks the first 3 elements to see if they are identical in each list, returning nil if any fail
; then calls helper function to compare the letter grade values. 
; if helper fails, nil is returned, otherwise t is returned
(defun meetsReqOLD (Req Act)
   (cond
      ((not (validGrade Req)) nil)
      ((not (validGrade Act)) nil)
      ((not (equalp (car Req) (car Act))) nil)
      ((not (equalp (car (cdr Req)) (car (cdr Act)))) nil)
      ((not (equalp (car (cdr (cdr Req))) (car (cdr (cdr Act))))) nil)
      (t (meetsReqhelp Req Act))
   )
)


; helper function for meetsReq
; takes two grades as lists
; first tests if the Act's lettergrade is "TRF", and returns t if so
; then gets the numerical values of each letter grade, converts any nil's to 0's
;  and does a comparison. if (Act >= Req), t returned
;  else, nil is returned
(defun meetsReqhelp (Req Act)
   (cond
      ((equalp (car (cdr (cdr (cdr Act)))) "TRF") t)
      ((>= 
         (niltozero (letterToGPA (car (cdr (cdr (cdr Act))))))
         (niltozero (letterToGPA (car (cdr (cdr (cdr Req))))))
      ) t)
      (t nil)
   )
)