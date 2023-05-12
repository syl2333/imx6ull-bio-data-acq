<template>
    <div>
        <v-text-field v-model="search" label="Search" solo clearable></v-text-field>
        <v-table>
            <thead>
                <tr>
                    <th class="text-center">
                        Date
                    </th>
                    <th class="text-center">
                        Data
                    </th>
                    <th class="text-center">
                        Action
                    </th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="item in paginatedData()" :key="item.date" >
                    <td>{{ item.date }}</td>
                    <td>{{ item.data }}</td>
                    <td>
                        <v-btn small flat class="btn-text-color" @click="viewItem(item)">View</v-btn>
                        <span>|</span>
                        <v-btn small flat  @click="editItem(item)">Edit</v-btn>
                        <span>|</span>
                        <v-btn small flat  @click="deleteItem(item)">Delete</v-btn>
                    </td>
                </tr>
            </tbody>
        </v-table>

        <v-pagination v-model="page" :length="totalPages" @input="handlePageChange"></v-pagination>



    </div>
</template>
  
<script>
import { ref } from 'vue';

export default {
    name: 'HistoryData',
    setup() {
        // 生成一些测试数据
        const headers = [
            { text: 'Date', align: 'start', sortable: false, value: 'date' },
            { text: 'Data', value: 'data' },
        ];
        const items = Array.from({ length: 50 }, (_, i) => ({
            date: `2023-01-${i + 1}`,
            data: Math.random() * 100,
        }));

        const itemsPerPage = ref(10);
        const page = ref(1);
        const totalPages = ref(Math.ceil(items.length / itemsPerPage.value));

        return {
            headers,
            items,
            itemsPerPage,
            page,
            totalPages,
        };
    },
    methods: {
        handlePageChange(newPage) {
            this.page.value = newPage;
        },
        paginatedData() {
            const start = (this.page - 1) * this.itemsPerPage;
            const end = start + this.itemsPerPage;
            return this.items.slice(start, end);
        },
        openModal(item) {
            this.selectedItem = item;
            this.dialogOpen = true;
        },
        viewItem(item) {
            // Handle view action here
            console.log(item)
        },
        editItem(item) {
            // Handle edit action here
            console.log(item)
        },
        deleteItem(item) {
            // Handle delete action here
            console.log(item)
        }
    }
};
</script>


<style scoped>
.btn-text-color {
  color: rgb(9, 112, 247); /* Change this to your preferred color */
}
span {
  margin: 0 5px;
}
</style>