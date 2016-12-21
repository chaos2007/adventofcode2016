module class_Keypad
    implicit none
    public :: Keypad, get_current_key, change_key, parse_line, keys, keys2
    
    character, dimension(0:2,0:2), target :: keys = reshape((/ '1', '2', '3', &
                                                      &'4', '5', '6', &
                                                      &'7', '8', '9' /), shape(keys))
    character, dimension(0:4,0:4), target :: keys2 = reshape((/ '0', '0', '1', '0', '0', &
                                                       &'0', '2', '3', '4', '5', &
                                                       &'5', '6', '7', '8', '9', &
                                                       &'0', 'A', 'B', 'C', '0', &
                                                       &'0', '0', 'D', '0', '0' /), shape(keys2))
    integer, dimension(1:2)  :: keys_dim = shape(keys)

    type Keypad
        integer :: current_x = 1
        integer :: current_y = 1 
        character, pointer, dimension(:,:) :: key => keys
    end type Keypad

    contains
        function get_current_key(this) result(key)
            type(Keypad), intent(in) :: this
            character :: key
            key = this%key(this%current_x, this%current_y)
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
            integer :: keys_size 
            integer, dimension(1:2)  :: keys_dim
            keys_dim = shape(this%key)
            keys_size = keys_dim(1)
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
             if( x >= 0 .and. y >= 0 .and. x < keys_size .and. y < keys_size .and. this%key(x, y) .ne. '0' ) then
                 this%current_x = x
                 this%current_y = y
             endif
        end subroutine change_key

end module class_Keypad

