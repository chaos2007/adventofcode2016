module class_Keypad
    implicit none
    public :: Keypad, get_current_key, change_key, parse_line
    
    integer, dimension(0:2,0:2) :: keys = reshape((/ 1, 2, 3, 4, 5, 6, 7, 8, 9 /), shape(keys))

    type Keypad
        integer :: current_x = 1
        integer :: current_y = 1
    end type Keypad

    contains
        function get_current_key(this) result(key)
            type(Keypad), intent(in) :: this
            integer :: key
            key = keys(this%current_x, this%current_y)
        end function get_current_key

        subroutine parse_line(this, line)
            type(Keypad), intent(inout) :: this
            character(len=*) :: line
            integer :: n
            do n = 1, len(line(:)) 
                call change_key(this, line(n:n))
            end do
        end subroutine

        subroutine change_key(this, direction) 
            type(Keypad), intent(inout) :: this
            character, intent(in) :: direction
            integer :: x, y
            x  = this%current_x
            y = this%current_y
            select case (direction)
                case('U')
                    y = y-1
                case('D')
                    y = y+1
                case('L')
                    x = x-1
                case('R')
                    x = x+1
                case default
                    call exit()
             end select
             if( x >= 0 .and. x <= 2 .and. y >= 0 .and. y <= 2) then
                 this%current_x = x
                 this%current_y = y
             endif
        end subroutine change_key

end module class_Keypad

