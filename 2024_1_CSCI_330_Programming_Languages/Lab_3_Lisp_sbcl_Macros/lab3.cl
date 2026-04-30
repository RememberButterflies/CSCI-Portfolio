;/**
; * @file lab3.cl
; * @author Patrick McGrath, CSCI 330, VIU
; * @version 1.0
; * @date March, 2024
; * 
; *  Lab 3 Lisp (sbcl) Macros
; *  Copyright (C) 2025 Patrick McGrath
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

(defvar C '("CSCI" 159 4 "C"))
(defvar D '("CSCI" 159 4 "D"))
(defvar Ap '("CSCI" 159 4 "A+"))
(defvar No '("CSCI" 159 4 "fart"))
(defvar math '("MATH" 159 4 "A"))



; (grArea G)
; ----------
; trusts G has valid form, returns the area (first element) of G
(defmacro grArea (G)
   `(car ,G)
   )

; (grNum G)
; ---------
; trusts G has valid form, returns the course number (second element) of G
(defmacro grNum (G)
   `(car (cdr ,G))
   )

; (grCred G)
; ----------
; trusts G has valid form, returns the credits (third element) of G
(defmacro grCred (G)
   `(car (cdr (cdr ,G)))
   )

; (grLetter G)
; ------------
; trusts G has valid form, returns the lettergrade (final element) of G
(defmacro grLetter (G)
   `(car (cdr (cdr (cdr ,G))))
   )


; list of letter grades ordered by [fictional] level of qualification,
;    any grade that appears later in list is treated as better than
;    any grade that appears earlier in list
; anything that doesn't appear in the list is treated as unqualified
(defconstant Letters '("D" "C-" "C" "CR" "C+" "B-" "B" "TRF" "B+" "A-" "A" "A+"))

; (letterRank G)
; --------------
; return nil if G's letter grade doesn't appear in Letters,
; otherwise return the position of L in Letters (0 to 11)
; Finds what position in Letters is equal to the letter grade of G with proper check if comparing strings first.
(defmacro letterRank (G)
   `(position (grLetter ,G) Letters :test #'string=)
)


; ALternate form of letterRank using helper function.
;(defmacro letterRank (G)
;   `(letrankhelp ,G Letters)
;)
;(defun letrankhelp (G L &optional (sofar 0))
;   (cond
;      ((equalp sofar 12) nil)
;      ((equalp (grLetter G) (car L)) sofar)
;      (t (letrankhelp G (cdr L) (+ sofar 1)))
;   )
;)

; (okGradeForm G)
; ---------------
; checks that G is structurally valid for a grade,
;   i.e. 4 element list whose types are (string integer integer string)
; returns t if G's form is correct, nil otherwise
; (does not check the area or lettergrade against VALIDAREAS or VALIDLETGRADES,
;  and does not check the range of values for the course number or credits)
(defmacro okGradeForm (G)
   `(cond
      ((null ,G) nil)
      ((not (listp ,G)) nil)
      ((not (equalp (length ,G) 4)) nil)
      ((not (stringp (car ,G))) nil)
      ((not (integerp (cadr ,G))) nil)
      ((not (integerp (caddr ,G))) nil)
      ((not (stringp (cadddr ,G))) nil)
      (t t)
   )
)


; (courseMatch C1 C2)
; -------------------
; if C1 and C2 both pass okGradeform and they have matching
;    areas, course numbers, and credits then t
; otherwise nil
(defmacro courseMatch (C1 C2)
   `(cond
      ((or (not (okGradeForm ,C1)) (not (okGradeForm ,C2))) nil)
      ((not (equalp (car ,C1) (car ,C2))) nil)
      ((not (equalp (cadr ,C1) (cadr ,C2))) nil)
      ((not (equalp (caddr ,C1) (caddr ,C2))) nil)
      (t t)
   )
)



; Does not work as intended.
; Passing a single parameter works as intended.
; Passing more than one parameter always produces true. 
; Alternate attemps produced always nil. 
; Macro produces two different codes depending on whether number of parameters is 1 or more.
; The first parameter is the required course, and the remaining parameters are the courses being checked against it.
; If only 1 parameter, then the inverse of okGradeForm of the parameter is returned.
; If more thant one parameter is passed, meetsReq is called on the first 2 parameters.
;  if they pass meetsReq, true is returned, 
;  otherwise, reqPassed is called on the first parameter and parameters 3+.
; (reqPassed R A1 A2 ... AN)
; --------------------------
; variadic macro: R is required, then zero or more A's
; true if R does not have okGradeForm
;   or if at least one actual course (the Ai's) meetsReq R
; false otherwise
(defmacro reqPassed (R &rest Actuals)
  (cond
    ((null Actuals) `(not (okGradeForm ,R)))
    (t `(if (meetsReq ,R (car ',Actuals)) 
            t
            (reqPassed ,R ,@(cdr Actuals))
         )
   )
   )
)







; (meetsReq R A)
; --------------
; A meets requirement R if:
;    R does not pass okGradeForm or
;    R and A both pass okGradeForm, and they courseMatch,
;      and either R's letterRank is nil or is <= A's letterRank
(defun meetsReq (R A)
   (cond
      ((not (okGradeForm R)) t)
      ((not (okGradeForm A)) nil)
      ((and
         (courseMatch R A)
         (or
            (null (letterRank R))
            (<= (letterRank R) (letterRank A))
         )
      ) t)
      (t nil)
   )
)