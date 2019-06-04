; ModuleID = 'InputFiles/_TP5_access/access.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i686-pc-linux-gnu"

@.str = private unnamed_addr constant [17 x i8] c"Enter passkey : \00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.2 = private unnamed_addr constant [15 x i8] c"Access Denied\0A\00", align 1
@.str.3 = private unnamed_addr constant [25 x i8] c"Disabled Access\0AExiting\0A\00", align 1
@.str.4 = private unnamed_addr constant [16 x i8] c"Access Granted\0A\00", align 1

; Function Attrs: nounwind
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %passkey = alloca i32, align 4
  %stored_key = alloca i32, align 4
  %count = alloca i32, align 4
  %tolerance_flag = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 9721, i32* %stored_key, align 4
  store i32 0, i32* %count, align 4
  store i32 5, i32* %tolerance_flag, align 4
  br label %2

; <label>:2                                       ; preds = %0, %18
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str, i32 0, i32 0))
  %4 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32* %passkey)
  %5 = load i32, i32* %passkey, align 4
  %6 = load i32, i32* %stored_key, align 4
  %7 = icmp eq i32 %5, %6
  br i1 %7, label %8, label %9

; <label>:8                                       ; preds = %2
  br label %19

; <label>:9                                       ; preds = %2
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i32 0, i32 0))
  %11 = load i32, i32* %count, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, i32* %count, align 4
  %13 = load i32, i32* %count, align 4
  %14 = load i32, i32* %tolerance_flag, align 4
  %15 = icmp eq i32 %13, %14
  br i1 %15, label %16, label %18

; <label>:16                                      ; preds = %9
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.3, i32 0, i32 0))
  store i32 -1, i32* %1, align 4
  br label %21

; <label>:18                                      ; preds = %9
  br label %2

; <label>:19                                      ; preds = %8
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0))
  store i32 0, i32* %1, align 4
  br label %21

; <label>:21                                      ; preds = %19, %16
  %22 = load i32, i32* %1, align 4
  ret i32 %22
}

declare i32 @printf(i8*, ...) #1

declare i32 @__isoc99_scanf(i8*, ...) #1

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 (tags/RELEASE_381/final)"}
